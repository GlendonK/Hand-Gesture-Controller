#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>

//#include <i2c/smbus.h> //needed for new i2c ver
#include <sys/ioctl.h>
#include <time.h>
#include "sensors.h"

float res[60]; // data stored here
float *dataReader(void)

{

    uint8_t fd = 0; // file descriptor to identify file opened
    volatile uint8_t i = 10;

    /* open i2c comms */
    if ((fd = open(I2C_PATH, O_RDWR)) < 0)
    {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if (ioctl(fd, I2C_SLAVE, IMU_ADDRESS) < 0)
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
    i2c_smbus_write_byte_data(fd, CTRL_REG1_G, 0b00000000);
    
    //accelerometer
    i2c_smbus_write_byte_data(fd, CTRL_REG3_M, 0b00000000); //continuos conversion mode
    i2c_smbus_write_byte_data(fd, FIFO_CTRL, 0b11000000);   // set to over write old samples
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0b00111000); // Enable X, Y, Z
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, 0b11000000); //ODR 952hz +-2g BW=408hz anti-aliasing=408hz
    i2c_smbus_write_byte_data(fd, CTRL_REG7_A, 0b11100000); // High Res mode, ODR/400 hz,

    //gyro
    i2c_smbus_write_byte_data(fd, CTRL_REG1_G, 0b11000011); //output data rate = 952hz, cutoff - 100hz
    i2c_smbus_write_byte_data(fd, CTRL_REG4, 0b00111000); // enable gyro x y z
    i2c_smbus_write_byte_data(fd, CTRL_REG3_G, 0b01000000); // high pass filter enabled
    i2c_smbus_write_byte_data(fd, CTRL_REG4_M, 0b00001000); // high-performace mode

    while (i > 0) /* 60 data will be read, 10 accelerometer x,y,z and 10 gyro x,y,z*/
    {
        /* read output from the accelerometer registers */
        uint8_t xLo = i2c_smbus_read_byte_data(fd, OUT_X_L_A);
        uint8_t yLo = i2c_smbus_read_byte_data(fd, OUT_Y_L_A);
        uint8_t zLo = i2c_smbus_read_byte_data(fd, OUT_Z_L_A);
        /* LSL 8 and 'OR' to append Lo behind of Hi */
        int16_t xHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_X_H_A)) << 8;
        int16_t yHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Y_H_A)) << 8;
        int16_t zHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Z_H_A)) << 8;
        int16_t accXTotal = (xHi | xLo);
        int16_t accYTotal = (yHi | yLo);
        int16_t accZTotal = (zHi | zLo);

        /* to set 2^15 as 0, below 2^15 as negative value, above 2^15 as positive values*/
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

        /* conversion for raw data mg/LSB to g/LSB*/
        res[i] = (float)((accXTotal)*ACCEL_MG_LSB_2G / 1000);
        //printf("acc_x: %f\n", res[i]);
        
        res[i] = (float)((accYTotal)*ACCEL_MG_LSB_2G / 1000);
        //printf("acc_yy: %f\n", res[i]);
        
        res[i] = (float)((accZTotal)*ACCEL_MG_LSB_2G / 1000);
        //printf("acc_z: %f\n", res[i]);
        //printf("\n");
        

        /*output for gyro data */
        uint8_t gxLo = i2c_smbus_read_byte_data(fd, OUT_X_L_G);
        uint8_t gyLo = i2c_smbus_read_byte_data(fd, OUT_Y_L_G);
        uint8_t gzLo = i2c_smbus_read_byte_data(fd, OUT_Z_L_G);
        int16_t gxHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_X_H_G) << 8);
        int16_t gyHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Y_H_G) << 8);
        int16_t gzHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Z_H_G) << 8);
        int16_t xtotal = (gxHi | gxLo);
        int16_t ytotal = (gyHi | gyLo);
        int16_t ztotal = (gzHi | gzLo);

        /* to set 2^15 as 0, below 2^15 as negative value, above 2^15 as positive values*/
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

        /* conversion for raw data mdps/LSB to dpsg(degree per sec * 9.81m/s^2) */
        res[i] = (float)(xtotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;
        //printf("gy_x: %f\n", res[i]);
        
        res[i] = (float)(ytotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;
        //printf("gy_y: %f\n", res[i]);
        
        res[i] = (float)(ztotal * GYRO_DPS_DIGIT_245DPS / 1000) * GRAVITY;
        //printf("gy_Z: %f\n", res[i]);
        //printf("\n");
        i--;
        //printf("%d", i);
    }

    close(fd);

    return res;
}
