#ifndef TASK_CONTROLE_H
#define TASK_CONTROLE_H

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "utils.h"
#include "sd_logger.h"
#include "config_btn.h"

void vTaskControle(void *params) {
    while (1) {
        // Verifica se o botão B foi pressionado para montar/desmontar o SD
        if (flag_montar_sd) {
            flag_montar_sd = false;

            if (!sd_montado) {
                if (montarSD()) {
                    if (iniciarCSV()) {
                        estado_atual = ESTADO_PRONTO;
                    } else {
                        estado_atual = ESTADO_ERRO_SD;
                    }
                } else {
                    estado_atual = ESTADO_ERRO_SD;
                }
            } else {
                desmontarSD();
                estado_atual = ESTADO_INICIALIZANDO;
            }
        }

        // Verifica se o botão A foi pressionado para iniciar/parar gravação
        if (flag_toggle_gravacao) {
            flag_toggle_gravacao = false;

            if (estado_atual == ESTADO_PRONTO) {
                estado_atual = ESTADO_GRAVANDO;
                gravando = true;
                numero_amostra = 0;
            } else if (estado_atual == ESTADO_GRAVANDO) {
                estado_atual = ESTADO_PRONTO;
                gravando = false;
            }
        }

        // Pequeno delay para não ocupar 100% da CPU
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

#endif
