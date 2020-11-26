/* file to collect data from gyro and accelerometer with C*/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <time.h>

#define IMU_ADDRESS 0x6A
#define I2C_PATH "/dev/i2c-1"

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

    int fda = 0; // i2c device id, 0 is the first device id
    int fdg = 1;
    uint8_t status = 0;

    /* open i2c comms */
    if ((fda = open(I2C_PATH, O_RDWR)) < 0 || (fdg = open(I2C_PATH, O_RDWR)) < 0)
    {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fda, I2C_SLAVE, IMU_ADDRESS) < 0 || ioctl(fdg, I2C_SLAVE, IMU_ADDRESS) < 0)
    {
        perror("Unable to configure i2c slave device");
        close(fda);
        close(fdg);
        exit(1);
    }

    /* check we are who we should be */
    if (i2c_smbus_read_byte_data(fda, WHO_AM_I) != 0x68 || i2c_smbus_read_byte_data(fdg, WHO_AM_I) != 0x68)
    {
        printf("%x\n", (i2c_smbus_read_byte_data(fda, WHO_AM_I)));
        printf("%x\n", (i2c_smbus_read_byte_data(fda, WHO_AM_I)));
        close(fda);
        close(fdg);
        exit(1);
    }

    /* Power down the device, reset */
    i2c_smbus_write_byte_data(fda, CTRL_REG6_A, 0b00000000);
    i2c_smbus_write_byte_data(fda, CTRL_REG5_A, 0b00000000);
    i2c_smbus_write_byte_data(fda, CTRL_REG3_M, 0b00000011);
    i2c_smbus_write_byte_data(fda, CTRL_REG2_M, 0b00001100);
    //i2c_smbus_write_byte_data(fd, CTRL_REG8, 0b00000100);

    i2c_smbus_write_byte_data(fdg, CTRL_REG1_G, 0b00000000);

    //accelerometer
    i2c_smbus_write_byte_data(fda, CTRL_REG3_M, 0b00000000); //continuos conversion mode
    i2c_smbus_write_byte_data(fda, FIFO_CTRL, 0b11000000);   // set to over write old samples
    i2c_smbus_write_byte_data(fda, CTRL_REG5_A, 0b00111000); // Enable X, Y, Z
    i2c_smbus_write_byte_data(fda, CTRL_REG6_A, 0b11000000); //ODR 952hz +-2g BW=408hz anti-aliasing=408hz
    i2c_smbus_write_byte_data(fda, CTRL_REG7_A, 0b11100000); // High Res mode, ODR/400 hz,
    //i2c_smbus_write_byte_data(fd, CTRL_REG9, 0b00000010);

    //gyro
    i2c_smbus_write_byte_data(fdg, CTRL_REG1_G, 0b11000011);
    i2c_smbus_write_byte_data(fdg, CTRL_REG4, 0b00111000);
    i2c_smbus_write_byte_data(fdg, CTRL_REG3_G, 0b01000000);
    //i2c_smbus_write_byte_data(fd, CTRL_REG2_G, 0b00000011);
    i2c_smbus_write_byte_data(fdg, CTRL_REG2_G, 0b00000000);
    i2c_smbus_write_byte_data(fda, CTRL_REG4_M, 0b00001000);

    FILE *fp;
    // opening an existing file
    printf("Opening the file test.c in write mode");
    fp = fopen("up1.csv", "a");
    
    int i = 0;
    int j = 0;
    int counter = 0;

    for (j; j < 100; j++)
    {
        // writing in the file
        /*printf("\nstart3.........\n");
	sleep(1);
	printf("\nstart2.........\n");
        sleep(1);*/
	printf("\nstart1.........\n");
        sleep(1);
        i = 0;
        for (i; i < 10; i++)
        {
            
            // LSL 8 and 'OR' to append Lo behind of Hi

            uint8_t xLo = i2c_smbus_read_byte_data(fda, OUT_X_L_A);
            uint8_t yLo = i2c_smbus_read_byte_data(fda, OUT_Y_L_A);
            uint8_t zLo = i2c_smbus_read_byte_data(fda, OUT_Z_L_A);
            int16_t xHi = ((int16_t)i2c_smbus_read_byte_data(fda, OUT_X_H_A)) << 8;
            int16_t yHi = ((int16_t)i2c_smbus_read_byte_data(fda, OUT_Y_H_A)) << 8;
            int16_t zHi = ((int16_t)i2c_smbus_read_byte_data(fda, OUT_Z_H_A)) << 8;

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

            res[0] = (float)((accXTotal)*conversion / 1000);
            res[1] = (float)((accYTotal)*conversion / 1000);
            res[2] = (float)((accZTotal)*conversion / 1000);

            uint8_t gxLo = i2c_smbus_read_byte_data(fdg, OUT_X_L_G);
            uint8_t gyLo = i2c_smbus_read_byte_data(fdg, OUT_Y_L_G);
            uint8_t gzLo = i2c_smbus_read_byte_data(fdg, OUT_Z_L_G);

            int16_t gxHi = ((int16_t)i2c_smbus_read_byte_data(fdg, OUT_X_H_G) << 8);
            int16_t gyHi = ((int16_t)i2c_smbus_read_byte_data(fdg, OUT_Y_H_G) << 8);
            int16_t gzHi = ((int16_t)i2c_smbus_read_byte_data(fdg, OUT_Z_H_G) << 8);

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

            /*printf("acc_x: %f\n", res[0]);
            printf("acc_yy: %f\n", res[1]);
            printf("acc_z: %f\n", res[2]);
            printf("\n");

            printf("gy_x: %f\n", gres[0]);
            printf("gy_y: %f\n", gres[1]);
            printf("gy_Z: %f\n", gres[2]);
            printf("\n"); */

            fprintf(fp, "%f,%f,%f,%f,%f,%f\n", res[0], res[1], res[2], gres[0], gres[1], gres[2]);
            printf("%d\n", counter);
            counter++;

            usleep(100000);
        }
        printf("\nend.......\n");
        sleep(1);
    }
    fclose(fp);

    close(fda);
    close(fdg);

    return (0);
}

