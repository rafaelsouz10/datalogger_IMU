#ifndef CONFIG_BTN_H
#define CONFIG_BTN_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Pinos dos botões
#define BTN_A 5  // Botão A → Iniciar/parar gravação
#define BTN_B 6  // Botão B → Montar/desmontar SD

// Flags globais (usadas pelas tasks)
volatile bool flag_toggle_gravacao = false;
volatile bool flag_montar_sd = false;

// Debounce
static volatile uint32_t last_time_us = 0;
#define DEBOUNCE_US 300000  // 300ms

// Função de interrupção única para ambos os botões
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t now = to_us_since_boot(get_absolute_time());
    if (now - last_time_us < DEBOUNCE_US) return;
    last_time_us = now;

    if (gpio == BTN_A) {
        flag_toggle_gravacao = true;
        printf("[IRQ] Botão A pressionado\n");
    } else if (gpio == BTN_B) {
        flag_montar_sd = true;
        printf("[IRQ] Botão B pressionado\n");
    }
}

// Inicialização dos botões e interrupções
void init_botoes() {
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    // Registra o callback apenas uma vez (para ambos)
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);

}

#endif
