#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <time.h>

#define DEV_ID 0x6a
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

#define GRAVITY (9.80665F) // gravity constant m/s^2

#define ACCEL_MG_LSB_2G (0.061F)
#define ACCEL_MG_LSB_4G (0.122F)
#define ACCEL_MG_LSB_8G (0.244F)
#define ACCEL_MG_LSB_16G (0.732F)

// Sensitivity of accelerometer
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
#define CTRL_REG3_M 0x22
#define CTRL_REG2_M 0x21
#define CTRL_REG8 0x22
#define CTRL_REG9 0x23

float res[3];
float conversion = 0.061F;


int main(void)
{

    int fd = 0; // i2c device id

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

    i2c_smbus_write_byte_data(fd, CTRL_REG3_M, 0b00000000); //continuos conversion mode
    i2c_smbus_write_byte_data(fd, FIFO_CTRL, 0b11000000);   // set to over write old samples
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0b00111000); // Enable X, Y, Z
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, 0b11000000); //ODR 952hz +-2g BW=408hz anti-aliasing=408hz
    i2c_smbus_write_byte_data(fd, CTRL_REG7_A, 0b11100000); // High Res mode, ODR/400 hz,
                                                            //i2c_smbus_write_byte_data(fd, CTRL_REG9, 0b00000010);

    while (1)
    {

        // LSL 8 and 'OR' to append Lo behind of Hi

        uint8_t xLo = i2c_smbus_read_byte_data(fd, OUT_X_L_A);
        uint8_t yLo = i2c_smbus_read_byte_data(fd, OUT_Y_L_A);
        uint8_t zLo = i2c_smbus_read_byte_data(fd, OUT_Z_L_A);
        int16_t xHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_X_H_A)) << 8;
        int16_t yHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Y_H_A)) << 8;
        int16_t zHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Z_H_A)) << 8;

        int16_t accXTotal = (xHi | xLo);
        int16_t accYTotal = (yHi | yLo);
        int16_t accZTotal = (zHi | zLo);

        if (xHi > 32767)
        {
            xHi = xHi - 65535;
        }
        if (yHi > 32767)
        {
            yHi = yHi - 65535;
        }
        if (zHi > 32767)
        {
            zHi = zHi - 65535;
        }

        res[0] = (float)((accXTotal)*conversion / 1000) * GRAVITY;
        res[1] = (float)((accYTotal)*conversion / 1000) * GRAVITY;
        res[2] = (float)((accZTotal)*conversion / 1000) * GRAVITY;

        printf("x: %f\n", res[0]);
        printf("y: %f\n", res[1]);
        printf("z: %f\n", res[2]);
        printf("\n");
        //printf("xLo: %x\n", xLo);
        //printf("yLo: %x\n", yLo);
        //printf("zLo: %x\n", zLo);
        printf("\n");
        //printf("xHi: %x\n", xHi);
        //printf("yHi: %x\n", yHi);
        //printf("zHi: %x\n", zHi);
        sleep(1);
    }

    close(fd);

    return (0);
}
