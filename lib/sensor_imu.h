#ifndef SENSOR_IMU_H
#define SENSOR_IMU_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Pinos e endereço do MPU6050
#define MPU_I2C i2c0
#define MPU_SDA 0
#define MPU_SCL 1
#define MPU_ADDR 0x68

// Inicializa o sensor MPU6050
void initMPU() {
    i2c_init(MPU_I2C, 400 * 1000);
    gpio_set_function(MPU_SDA, GPIO_FUNC_I2C);
    gpio_set_function(MPU_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(MPU_SDA);
    gpio_pull_up(MPU_SCL);

    // Wake up MPU6050
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(MPU_I2C, MPU_ADDR, buf, 2, false);
    sleep_ms(100);
}

// Lê os dados brutos da IMU
bool lerDadosMPU(int16_t *accelX, int16_t *accelY, int16_t *accelZ,
                 int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ) {
    uint8_t reg = 0x3B; // Endereço do primeiro registrador (ACCEL_XOUT_H)
    uint8_t buffer[14];

    // Solicita os 14 bytes de dados
    if (i2c_write_blocking(MPU_I2C, MPU_ADDR, &reg, 1, true) < 0)
        return false;

    if (i2c_read_blocking(MPU_I2C, MPU_ADDR, buffer, 14, false) < 0)
        return false;

    *accelX = (buffer[0] << 8) | buffer[1];
    *accelY = (buffer[2] << 8) | buffer[3];
    *accelZ = (buffer[4] << 8) | buffer[5];

    *gyroX  = (buffer[8] << 8) | buffer[9];
    *gyroY  = (buffer[10] << 8) | buffer[11];
    *gyroZ  = (buffer[12] << 8) | buffer[13];

    return true;
}

#endif
