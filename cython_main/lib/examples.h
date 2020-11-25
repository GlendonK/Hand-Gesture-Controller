#ifndef EXAMPLES_H
#define EXAMPLES_H

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

void hello(const char *name);
float* dataReader(void);
#endif