#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Declaração dos pinos das colunas e linhas do teclado matricial
const uint8_t colunas[4] = {4, 3, 2, 1};
const uint8_t linhas[4] = {5, 6, 7, 8};

// Declaração dos pinos dos LEDs e do buzzer
const uint8_t PIN_LED_R = 13;
const uint8_t PIN_LED_B = 12;
const uint8_t PIN_LED_G = 11;
const uint8_t PIN_BUZZER = 21;
const uint32_t freq = 350; // Frequência do buzzer em Hz

// Função para ligar os LEDs
void turn_on_led(bool red, bool blue, bool green) {
    gpio_put(PIN_LED_R, red);
    gpio_put(PIN_LED_B, blue);
    gpio_put(PIN_LED_G, green);
}

// Mapeamento das teclas do teclado matricial
const char teclado[4][4] = {
    {'1', '2', '3', 'A'}, 
    {'4', '5', '6', 'B'}, 
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Protótipo da função para leitura do teclado
char leitura_teclado();

int main() {
    stdio_init_all(); // Inicialização da entrada e saída padrão

    // Inicialização dos pinos dos LEDs como saída
    gpio_init(PIN_LED_R);
    gpio_set_dir(PIN_LED_R, GPIO_OUT);
    gpio_init(PIN_LED_B);
    gpio_set_dir(PIN_LED_B, GPIO_OUT);
    gpio_init(PIN_LED_G);
    gpio_set_dir(PIN_LED_G, GPIO_OUT);
    
    // Configuração do buzzer como PWM
    gpio_set_function(PIN_BUZZER, GPIO_FUNC_PWM);
    int slice_num = pwm_gpio_to_slice_num(PIN_BUZZER); // Obtenção do slice de PWM
    
    uint32_t clk_sys = clock_get_hz(clk_sys); // Frequência do sistema
    uint16_t wrap = clk_sys / freq - 1; // Cálculo do valor de wrap
    
    pwm_set_wrap(slice_num, wrap); // Configuração do valor de wrap
    pwm_set_gpio_level(PIN_BUZZER, wrap / 2); // Configuração do nível de PWM
    
    // Inicialização dos pinos das colunas do teclado como saída
    for (int i = 0; i < 4; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_OUT);
        gpio_put(colunas[i], 1); // Colunas inicialmente em nível alto
    }

    // Inicialização dos pinos das linhas do teclado como entrada com pull-up
    for (int i = 0; i < 4; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_IN);
        gpio_pull_up(linhas[i]);
    }

    while (true) {    
        char tecla = leitura_teclado(); // Leitura do teclado
        
        // Ação baseada na tecla pressionada
        switch(tecla) {
            case '1':
                gpio_put(PIN_LED_R, 1); // Liga LED vermelho
                break;
            case '2':
                gpio_put(PIN_LED_R, 0); // Desliga LED vermelho
                break;
            case '3':
                gpio_put(PIN_LED_B, 1); // Liga LED azul
                break;
            case '4':
                gpio_put(PIN_LED_B, 0); // Desliga LED azul
                break;
            case '5':
                gpio_put(PIN_LED_G, 1); // Liga LED verde
                break;
            case '6':
                gpio_put(PIN_LED_G, 0); // Desliga LED verde
                break;
            case '7':
                pwm_set_enabled(slice_num, true); // Liga o buzzer
                break;
            case '8':
                pwm_set_enabled(slice_num, false); // Desliga o buzzer
                break;
            default:
                break;
        }
        
        sleep_ms(200); // Atraso para evitar múltiplas leituras da mesma tecla
    }

    return 0;
}

// Função para leitura do teclado matricial
char leitura_teclado() {
    char numero = 'n'; // Valor padrão caso nenhuma tecla seja pressionada

    for (int coluna = 0; coluna < 4; coluna++) {
        gpio_put(colunas[coluna], 0); // Coluna ativa em nível baixo

        for (int linha = 0; linha < 4; linha++) {
            if (gpio_get(linhas[linha]) == 0) {
                numero = teclado[3 - linha][coluna]; // Mapeamento da tecla pressionada
                while (gpio_get(linhas[linha]) == 0) {
                    sleep_ms(10); // Espera enquanto a tecla estiver pressionada
                }
                break;
            }
        }

        gpio_put(colunas[coluna], 1); // Coluna desativada em nível alto

        if (numero != 'n') {
            break; // Sai do loop se uma tecla foi pressionada
        }
    }

    return numero; // Retorna a tecla pressionada
}
