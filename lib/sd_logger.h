#ifndef SD_LOGGER_H
#define SD_LOGGER_H

#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "sd_card.h"
#include "hw_config.h"

#include "pico/stdlib.h"
#include "utils.h"  // Para acessar estado_atual

// Nome do arquivo CSV
static const char *NOME_ARQUIVO = "dados_imu.csv";

// Objeto do arquivo e status FatFs
static FIL arquivo_csv;
static bool arquivo_aberto = false;

// Monta o cartão SD
bool montarSD() {
    sd_card_t *sd = sd_get_by_num(0);
    FRESULT res = f_mount(&sd->fatfs, sd->pcName, 1);
    if (res == FR_OK) {
        sd_montado = true;
        return true;
    } else {
        sd_montado = false;
        estado_atual = ESTADO_ERRO_SD;
        return false;
    }
}

// Desmonta o cartão SD com segurança
void desmontarSD() {
    if (arquivo_aberto) {
        f_close(&arquivo_csv);
        arquivo_aberto = false;
    }
    f_unmount("0:");
    sd_montado = false;
}

// Cria ou reabre o CSV e escreve o cabeçalho
bool iniciarCSV() {
    FRESULT res = f_open(&arquivo_csv, NOME_ARQUIVO, FA_WRITE | FA_OPEN_APPEND);
    if (res != FR_OK) {
        estado_atual = ESTADO_ERRO_SD;
        return false;
    }

    const char *cabecalho = "numero_amostra;accel_x;accel_y;accel_z;gyro_x;gyro_y;gyro_z\n";
    UINT escritos;
    res = f_write(&arquivo_csv, cabecalho, strlen(cabecalho), &escritos);
    if (res != FR_OK) {
        f_close(&arquivo_csv);
        estado_atual = ESTADO_ERRO_SD;
        return false;
    }

    arquivo_aberto = true;
    return true;
}

// Salva uma linha com os dados no CSV
bool salvarLinhaCSV(uint32_t amostra, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) {
    if (!arquivo_aberto) return false;

    char linha[128];
    snprintf(linha, sizeof(linha), "%lu;%d;%d;%d;%d;%d;%d\n", 
        amostra, ax, ay, az, gx, gy, gz);

    UINT escritos;
    FRESULT res = f_write(&arquivo_csv, linha, strlen(linha), &escritos);
    if (res != FR_OK) {
        estado_atual = ESTADO_ERRO_SD;
        return false;
    }

    // Opcional: forçar flush para cartão (maior segurança, menor desempenho)
    f_sync(&arquivo_csv);

    return true;
}

#endif
