#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <time.h>

#define DEV_ID 0x6A
#define DEV_PATH "/dev/i2c-1"

// Accelerometer addresses
#define WHO_AM_I 0x0F    // device identifier
#define CTRL_REG5_A 0x1F //_A is accelerometer registers
#define CTRL_REG6_A 0x20
#define CTRL_REG7_A 0x21
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D

#define OUT_X_L_G 0x18
#define OUT_X_H_G 0x19
#define OUT_Y_L_G 0x1A
#define OUT_Y_H_G 0x1B
#define OUT_Z_L_G 0x1C
#define OUT_Z_H_G 0x1D

#define GRAVITY (9.80665F) // gravity constant m/s^2
// Sensitivity of accelerometer
#define ACCEL_MG_LSB_2G (0.061F)
#define ACCEL_MG_LSB_4G (0.122F)
#define ACCEL_MG_LSB_8G (0.244F)
#define ACCEL_MG_LSB_16G (0.732F)
/*
#define MAG_MGAUSS_4GAUSS      (0.16F)
#define MAG_MGAUSS_8GAUSS      (0.32F)
#define MAG_MGAUSS_12GAUSS     (0.48F)
#define MAG_MGAUSS_16GAUSS     (0.58F)
*/

// Gyro dps settings
#define GYRO_DPS_DIGIT_245DPS (0.00875F)
#define GYRO_DPS_DIGIT_500DPS (0.01750F)
#define GYRO_DPS_DIGIT_2000DPS (0.07000F)

#define STATUS_REG 0x27
#define FIFO_CTRL 0x2E
#define CTRL_REG3_M 0x22 //_M for magnetometer register
#define CTRL_REG2_M 0x21
#define CTRL_REG8 0x22
#define CTRL_REG9 0x23
#define CTRL_REG1_G 0x10 // _G for gyro registers
#define CTRL_REG4 0x1E
#define CTRL_REG3_G 0x12
#define CTRL_REG2_G 0x11
#define CTRL_REG4_M 0x23

float res[3];
float gres[3];
float conversion = ACCEL_MG_LSB_2G;


int main(void)
{

    int fd = 0; // i2c device id, 0 is the first device id

    uint8_t status = 0;

    /* open i2c comms */
    if ((fd = open(DEV_PATH, O_RDWR)) < 0)
    {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, DEV_ID) < 0)
    {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fd, WHO_AM_I) != 0x68)
    {
        printf("%x\n", (i2c_smbus_read_byte_data(fd, WHO_AM_I)));
        close(fd);
        exit(1);
    }

    /* Power down the device, reset */
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, 0b00000000);
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0b00000000);
    i2c_smbus_write_byte_data(fd, CTRL_REG3_M, 0b00000011);
    i2c_smbus_write_byte_data(fd, CTRL_REG2_M, 0b00001100);
    //i2c_smbus_write_byte_data(fd, CTRL_REG8, 0b00000100);

    i2c_smbus_write_byte_data(fd, CTRL_REG1_G, 0b00000000);

    //accelerometer
    i2c_smbus_write_byte_data(fd, CTRL_REG3_M, 0b00000000); //continuos conversion mode
    i2c_smbus_write_byte_data(fd, FIFO_CTRL, 0b11000000);   // set to over write old samples
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0b00111000); // Enable X, Y, Z
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, 0b11000000); //ODR 952hz +-2g BW=408hz anti-aliasing=408hz
    i2c_smbus_write_byte_data(fd, CTRL_REG7_A, 0b11100000); // High Res mode, ODR/400 hz,
    //i2c_smbus_write_byte_data(fd, CTRL_REG9, 0b00000010);

    //gyro
    i2c_smbus_write_byte_data(fd, CTRL_REG1_G, 0b11000011);
    i2c_smbus_write_byte_data(fd, CTRL_REG4, 0b00111000);
    i2c_smbus_write_byte_data(fd, CTRL_REG3_G, 0b01000000);
    //i2c_smbus_write_byte_data(fd, CTRL_REG2_G, 0b00000011);
    i2c_smbus_write_byte_data(fd, CTRL_REG2_G, 0b00000000);
    i2c_smbus_write_byte_data(fd, CTRL_REG4_M, 0b00001000);

    while (1)
    {

        // LSL 8 and 'OR' to append Lo behind of Hi

        uint8_t gxLo = i2c_smbus_read_byte_data(fd, OUT_X_L_G);
        uint8_t gyLo = i2c_smbus_read_byte_data(fd, OUT_Y_L_G);
        uint8_t gzLo = i2c_smbus_read_byte_data(fd, OUT_Z_L_G);

        int16_t gxHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_X_H_G) << 8);
        int16_t gyHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Y_H_G) << 8);
        int16_t gzHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Z_H_G) << 8);

        int16_t xtotal = (gxHi | gxLo);
        int16_t ytotal = (gyHi | gyLo);
        int16_t ztotal = (gzHi | gzLo);

        if (xtotal > 32767)
        {
            xtotal = xtotal - 65535;
        }
        if (ytotal > 32767)
        {
            ytotal = ytotal - 65535;
        }
        if (ztotal > 32767)
        {
            ztotal = ztotal - 65535;
        }

        gres[0] = (float)(xtotal * 0.00875 / 1000) * GRAVITY;
        gres[1] = (float)(ytotal * 0.00875 / 1000) * GRAVITY;
        gres[2] = (float)(ztotal * 0.00875 / 1000) * GRAVITY;

        printf("x: %f\n", gres[0]);
        printf("y: %f\n", gres[1]);
        printf("Z: %f\n", gres[2]);
        printf("\n");
        sleep(1);
    }

    close(fd);

    return (0);
}
