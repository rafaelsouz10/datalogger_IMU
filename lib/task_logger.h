#ifndef TASK_LOGGER_H
#define TASK_LOGGER_H

#include "pico/stdlib.h"
#include "utils.h"
#include "sensor_imu.h"
#include "sd_logger.h"

// Define o intervalo de coleta em milissegundos
#define INTERVALO_LOG_MS 500

void vTaskLogger(void *params) {
    const TickType_t xDelay = pdMS_TO_TICKS(INTERVALO_LOG_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // Variáveis para armazenar leitura
    int16_t ax, ay, az, gx, gy, gz;

    while (1) {
        // Executa somente se estiver gravando
        if (estado_atual == ESTADO_GRAVANDO) {
            bool leitura_ok = lerDadosMPU(&ax, &ay, &az, &gx, &gy, &gz);

            if (leitura_ok) {
                numero_amostra++;
                salvarLinhaCSV(numero_amostra, ax, ay, az, gx, gy, gz);
            }
        }

        // Aguarda o próximo ciclo
        vTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}

#endif
