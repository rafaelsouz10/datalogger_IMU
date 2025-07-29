#ifndef TASK_DISPLAY_H
#define TASK_DISPLAY_H

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"

#include "utils.h"  // Para estado_atual, numero_amostra, etc.

// I2C do display
#define I2C_PORT_DISP i2c1
#define SDA_DISP 14
#define SCL_DISP 15
#define DISPLAY_ADDR 0x3C

void vTaskDisplay(void *pvParameters) {
    i2c_init(I2C_PORT_DISP, 400 * 1000);
    gpio_set_function(SDA_DISP, GPIO_FUNC_I2C);
    gpio_set_function(SCL_DISP, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_DISP);
    gpio_pull_up(SCL_DISP);

    ssd1306_t ssd;
    ssd1306_init(&ssd, 128, 64, false, DISPLAY_ADDR, I2C_PORT_DISP);
    ssd1306_config(&ssd);

    char str_amostra[22];

    while (1) {
        ssd1306_fill(&ssd, false);

        // Título fixo
        ssd1306_draw_string(&ssd, "DATALOGGER IMU", 10, 0);

        // Mensagens dinâmicas
        switch (estado_atual) {
            case ESTADO_INICIALIZANDO:
            ssd1306_draw_string(&ssd, "SD desmontado", 10, 15);
                ssd1306_draw_string(&ssd, "Pressione B", 10, 30);
                ssd1306_draw_string(&ssd, "p/ montar", 25, 45);
            break;
            case ESTADO_PRONTO:
                ssd1306_draw_string(&ssd, "SD montado", 20, 15);
                ssd1306_draw_string(&ssd, "Para gravar", 0, 30);
                ssd1306_draw_string(&ssd, "Pressione A", 20, 45);
            break;
            case ESTADO_GRAVANDO:
                sprintf(str_amostra, "Amostra: %lu", numero_amostra);
                ssd1306_draw_string(&ssd, "Gravando...", 20, 25);
                ssd1306_draw_string(&ssd, str_amostra, 15, 45);
            break;
            case ESTADO_ERRO_SD:
                ssd1306_draw_string(&ssd, "ERRO no SD!", 25, 25);
            break;
            default:
                ssd1306_draw_string(&ssd, "Estado indefinido", 0, 30);
            break;
        }

        ssd1306_send_data(&ssd);
        vTaskDelay(pdMS_TO_TICKS(500));  // Atualiza a cada 0.5s
    }
}

#endif
