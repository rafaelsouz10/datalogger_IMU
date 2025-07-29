#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "lib/utils.h"  // Inclui os externs

// Aqui definimos as variáveis globais
volatile EstadoSistema estado_atual = ESTADO_INICIALIZANDO;
volatile bool sd_montado = false;
volatile bool gravando = false;
volatile uint32_t numero_amostra = 0;

// Módulos personalizados
#include "lib/utils.h"
#include "lib/task_controle.h"
#include "lib/sensor_imu.h"
#include "lib/sd_logger.h"
#include "lib/task_logger.h"
#include "lib/config_btn.h"
#include "lib/task_display.h"

int main() {
    stdio_init_all();
    sleep_ms(2000); // Aguardar estabilização da USB
    
    init_botoes();

    // Inicializa o sensor IMU
    initMPU();


    estado_atual = ESTADO_INICIALIZANDO;

    xTaskCreate(vTaskControle, "Controle", 1024, NULL, 2, NULL);
    xTaskCreate(vTaskLogger, "Logger", 1024, NULL, 2, NULL);
    xTaskCreate(vTaskDisplay, "Display", 1024, NULL, 1, NULL);

    // Inicia o agendador do FreeRTOS
    vTaskStartScheduler();

    return 0;
}
