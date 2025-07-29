#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

// Estados possíveis do sistema
typedef enum {
    ESTADO_INICIALIZANDO,
    ESTADO_MONTANDO_SD,
    ESTADO_PRONTO,
    ESTADO_GRAVANDO,
    ESTADO_DESMONTANDO_SD,
    ESTADO_ERRO_SD
} EstadoSistema;

// Variáveis globais de estado
extern volatile EstadoSistema estado_atual;
extern volatile bool sd_montado;
extern volatile bool gravando;
extern volatile uint32_t numero_amostra;

#endif
