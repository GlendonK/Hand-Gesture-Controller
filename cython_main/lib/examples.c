#include <stdio.h>

#include <stdint.h>

#include <unistd.h>

#include <linux/i2c-dev.h>

#include <stdlib.h>

#include <fcntl.h>

//#include <i2c/smbus.h>

#include <sys/ioctl.h>

#include <time.h>

#include "examples.h"

/* im so sorry this have to be global to pass to python 
    and i cant free it as it needs to be read by other py functions*/
float res[60];

float *dataReader(void)

{

    int fda = 0; // i2c device id, 0 is the first device id

    int fdg = 1;

    int i = 0;

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

    i2c_smbus_write_byte_data(fda, FIFO_CTRL, 0b11000000); // set to over write old samples

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

    while (i < 60)

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

        res[i] = (float)((accXTotal)*ACCEL_MG_LSB_2G / 1000);

        printf("acc_x: %f\n", res[i]);

        i++;

        res[i] = (float)((accYTotal)*ACCEL_MG_LSB_2G / 1000);

        printf("acc_yy: %f\n", res[i]);

        i++;

        res[i] = (float)((accZTotal)*ACCEL_MG_LSB_2G / 1000);

        printf("acc_z: %f\n", res[i]);

        printf("\n");

        i++;

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

        res[i] = (float)(xtotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;

        printf("gy_x: %f\n", res[i]);

        i++;

        res[i] = (float)(ytotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;

        printf("gy_y: %f\n", res[i]);

        i++;

        res[i] = (float)(ztotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;

        printf("gy_Z: %f\n", res[i]);

        printf("\n");

        i++;

        printf("%d", i);

        usleep(100000);

    } //printf("\n THE res[i] IS: %f\n",res[60]);

    close(fda);

    close(fdg);

    return res;
}
