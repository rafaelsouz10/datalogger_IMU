#ifndef TASK_ALARME_H
#define TASK_ALARME_H

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "utils.h"

// GPIOs do LED RGB
#define LED_R 13
#define LED_G 12
#define LED_B 11
#define BUZZER 21

// Controle do buzzer
volatile bool buzzer_estado = false;
alarm_id_t buzzer_alarm_id = -1;

// Callback de interrupção sonora (~500Hz)
int64_t buzzer_alarm_callback(alarm_id_t id, void *user_data) {
    buzzer_estado = !buzzer_estado;
    gpio_put(BUZZER, buzzer_estado);
    return 2000; // 2ms = 500Hz
}

// Inicia bip sonoro
void buzzer_start_alarm() {
    if (buzzer_alarm_id < 0)
        buzzer_alarm_id = add_alarm_in_us(2000, buzzer_alarm_callback, NULL, true);
}

// Para o bip
void buzzer_stop_alarm() {
    if (buzzer_alarm_id >= 0) {
        cancel_alarm(buzzer_alarm_id);
        buzzer_alarm_id = -1;
        gpio_put(BUZZER, 0);
        buzzer_estado = false;
    }
}

// Ativa cor RGB
void set_rgb(bool r, bool g, bool b) {
    gpio_put(LED_R, r);
    gpio_put(LED_G, g);
    gpio_put(LED_B, b);
}

// Task principal de alerta
void vTaskAlarme(void *params) {
    gpio_init(LED_R); gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G); gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B); gpio_set_dir(LED_B, GPIO_OUT);
    gpio_init(BUZZER); gpio_set_dir(BUZZER, GPIO_OUT);
    buzzer_stop_alarm();

    bool piscando = false;
    bool gravando_anterior = false;

    while (1) {
        switch (estado_atual) {
            case ESTADO_INICIALIZANDO:
                set_rgb(1, 1, 0); // Amarelo
                break;
            case ESTADO_PRONTO:
                set_rgb(0, 1, 0); // Verde
                break;
            case ESTADO_GRAVANDO:
                set_rgb(1, 0, 0); // Vermelho
                break;
            case ESTADO_ERRO_SD:
                set_rgb(piscando, 0, piscando); // Roxo piscando
                break;
            default:
                set_rgb(0, 0, 0); // Desligado
                break;
        }

        // Efeito de acesso SD (azul piscando rápido)
        if (estado_atual == ESTADO_GRAVANDO && (numero_amostra % 20 == 0)) {
            set_rgb(0, 0, 1); // Azul
            vTaskDelay(pdMS_TO_TICKS(100));
            set_rgb(1, 0, 0); // Vermelho de volta
        }

        // Sinal sonoro: 1 beep ao iniciar gravação
        if (estado_atual == ESTADO_GRAVANDO && !gravando_anterior) {
            buzzer_start_alarm();
            vTaskDelay(pdMS_TO_TICKS(100));
            buzzer_stop_alarm();
            gravando_anterior = true;
        }

        // Sinal sonoro: 2 beeps ao parar gravação
        if (gravando_anterior && estado_atual != ESTADO_GRAVANDO) {
            buzzer_start_alarm();
            vTaskDelay(pdMS_TO_TICKS(100));
            buzzer_stop_alarm();
            vTaskDelay(pdMS_TO_TICKS(50));
            buzzer_start_alarm();
            vTaskDelay(pdMS_TO_TICKS(100));
            buzzer_stop_alarm();
            gravando_anterior = false;
        }

        piscando = !piscando;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

#endif
