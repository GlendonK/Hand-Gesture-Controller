/*
 *  C code to read pressure and temperature from the
 *  Raspberry Pi Sense HAT add-on board (LPS25H sensor)
 *
 *  sudo raspi-config --> interfacing options --> enable i2c
 *
 *  sudo apt install libi2c-dev
 *
 *  Build with:  gcc -Wall -O2 pressure.c -o pressure -li2c
 *
 *  Tested with:  Raspbian GNU/Linux 10 (buster) / Raspberry Pi 3 B+
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <i2c/smbus.h>
#include <sys/ioctl.h>

#define DEV_ID 0x1c
#define DEV_PATH "/dev/i2c-1"


// Accelerometer addresses
#define WHO_AM_I     0x0F
#define CTRL_REG5_A     0x1F
#define CTRL_REG6_A     0x20
#define CTRL_REG7_A     0x21
#define OUT_X_L_A       0x28
#define OUT_X_H_A       0x29
#define OUT_Y_L_A       0x2A
#define OUT_Y_H_A       0x2B
#define OUT_Z_L_A       0x2C
#define OUT_Z_H_A       0x2D

#define GRAVITY (9.80665F)

#define ACCEL_MG_LSB_2G  (0.061F)
#define ACCEL_MG_LSB_4G  (0.122F)
#define ACCEL_MG_LSB_8G  (0.244F)
#define ACCEL_MG_LSB_16G (0.732F) // Is this right? Was expecting 0.488F

#define MAG_MGAUSS_4GAUSS      (0.16F)
#define MAG_MGAUSS_8GAUSS      (0.32F)
#define MAG_MGAUSS_12GAUSS     (0.48F)
#define MAG_MGAUSS_16GAUSS     (0.58F)

#define GYRO_DPS_DIGIT_245DPS      (0.00875F)
#define GYRO_DPS_DIGIT_500DPS      (0.01750F)
#define GYRO_DPS_DIGIT_2000DPS     (0.07000F)

float res[3];
float conversion = 0.061F;

void delay(int);

int main(void)
{
    int fd = 0;
    uint8_t temp_out_l = 0, temp_out_h = 0;
    int16_t temp_out = 0;
    double t_c = 0.0;

    uint8_t press_out_xl = 0;
    uint8_t press_out_l = 0;
    uint8_t press_out_h = 0;

    int32_t press_out = 0;
    double pressure = 0.0;

    uint8_t status = 0;

    /* open i2c comms */
    if((fd = open(DEV_PATH, O_RDWR)) < 0) {
        perror("Unable to open i2c device");
        exit(1);
    }

    /* configure i2c slave */
    if(ioctl(fd, I2C_SLAVE, DEV_ID) < 0) {
        perror("Unable to configure i2c slave device");
        close(fd);
        exit(1);
    }

    /* check we are who we should be */
    if(i2c_smbus_read_byte_data(fd, WHO_AM_I) != 0x3D) {
        printf("%x\n",(i2c_smbus_read_byte_data(fd, WHO_AM_I)));
        close(fd);
        exit(1);
    }

    #ifdef SERIES0
    i2c_smbus_write_byte_data(fd, CTRL_REG1_A, 0xA7);
    i2c_smbus_write_byte_data(fd, CTRL_REG2_A, range);
#elif SERIES1
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0x38);   // Enable X, Y, Z
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, 0xC0);   // 1 KHz out data rate, BW set by ODR, 408Hz anti-aliasing
    uint8_t reg = i2c_smbus_read_byte_data(fd, CTRL_REG6_A);
    reg &= ~(0b00011000);
    reg |= range;
    i2c_smbus_write_byte_data(fd, CTRL_REG6_A, reg);
#endif
 uint8_t xLo = i2c_smbus_read_byte_data(fd, OUT_X_L_A);
 uint8_t yLo = i2c_smbus_read_byte_data(fd, OUT_Y_L_A);
 uint8_t zLo = i2c_smbus_read_byte_data(fd, OUT_Z_L_A);
    int16_t xHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_X_H_A)) << 8;
    int16_t yHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Y_H_A)) << 8;
    int16_t zHi = ((int16_t)i2c_smbus_read_byte_data(fd, OUT_Z_H_A)) << 8;
    res[0] = (long)((xHi | xLo) * conversion / 1000) * GRAVITY;
    res[1] = (long)((yHi | yLo) * conversion / 1000) * GRAVITY;
    res[2] = (long)((zHi | zLo) * conversion / 1000) * GRAVITY;


    /* Power down the device */
    i2c_smbus_write_byte_data(fd, CTRL_REG5_A, 0x00);
    printf("x: %lf\n", res[0]);
    printf("y: %lf\n", res[1]);
    printf("z: %lf\n", res[2]);
    printf("\n");
    printf("xHi: %x\n", xHi);
    printf("yHi: %x\n", yHi);
    printf("zHi: %x\n", zHi);
    
    

    close(fd);

    return (0);
}

void delay(int t)
{
    usleep(t * 1000);
}
