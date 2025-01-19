#include <stdio.h>
#include "pico/stdlib.h"

#define RGB_VERDE 11
#define RGB_AZUL 12
#define RGB_VERMELHO 13
#define BUZZER 21

#define L1 2
#define L2 3
#define L3 4
#define L4 5
#define C1 6
#define C2 7
#define C3 8
#define C4 9

uint linhas[4] = {8, 7, 6, 5};
uint colunas[4] = {4, 3, 2, 1}; 

char key_map[4][4]= {
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

void init_keyboard() {
    gpio_init(L1);
    gpio_set_dir(L1, GPIO_OUT);
    gpio_put(L1, false);

    gpio_init(L2);
    gpio_set_dir(L2, GPIO_OUT);
    gpio_put(L2, false);

    gpio_init(L3);
    gpio_set_dir(L3, GPIO_OUT);
    gpio_put(L3, false);

    gpio_init(L4);
    gpio_set_dir(L4, GPIO_OUT);
    gpio_put(L4, false);

    gpio_init(C1);
    gpio_set_dir(C1, GPIO_IN);
    gpio_pull_down(C1);

    gpio_init(C2);
    gpio_set_dir(C2, GPIO_IN);
    gpio_pull_down(C2);

    gpio_init(C3);
    gpio_set_dir(C3, GPIO_IN);
    gpio_pull_down(C3);

    gpio_init(C4);
    gpio_set_dir(C4, GPIO_IN);
    gpio_pull_down(C4);
}

void setup(){
    gpio_init(RGB_VERDE);
    gpio_set_dir(RGB_VERDE, GPIO_OUT);
    gpio_put(RGB_VERDE, false);

    gpio_init(RGB_AZUL);
    gpio_set_dir(RGB_AZUL, GPIO_OUT);
    gpio_put(RGB_AZUL, false);

    gpio_init(RGB_VERMELHO);
    gpio_set_dir(RGB_VERMELHO, GPIO_OUT);
    gpio_put(RGB_VERMELHO, false);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, false);
}

char ler_teclado(){
    for (int i = 0; i < 4; i++) {
        gpio_put(L1 + i, 1);

        for (int j = 0; j < 4; j++) {
            if (gpio_get(C1 + j)) {
                sleep_ms(50);

                while (gpio_get(C1 + j)); 

                gpio_put(L1 + i, 0); 

                return key_map[i][j];
            }
        }
        gpio_put(L1 + i, 0);
    }
}

void reset() {
    gpio_put(RGB_VERDE, false);
    gpio_put(RGB_AZUL, false);
    gpio_put(RGB_VERMELHO, false);
}
int main(){
    stdio_init_all();
    init_keyboard();
    setup();

    while (true) {
        char tecla = ler_teclado();
        printf("\nTecla pressionada: %c\n", tecla);
        switch (tecla){
            case '1': 
            case '4': 
            case '7': 
            case '*':
            reset();
            gpio_put(RGB_VERDE, true);
            break;
            
            case '2': 
            case '5': 
            case '8': 
            case '0':
            reset();
            gpio_put(RGB_AZUL, true);
            break;

            case '3': 
            case '6': 
            case '9': 
            case '#':
            reset();
            gpio_put(RGB_VERMELHO, true);
            break;

            case 'A': 
            case 'C': 
            case 'D':
            reset();
            gpio_put(RGB_VERDE, true);
            gpio_put(RGB_AZUL, true);
            gpio_put(RGB_VERMELHO, true);
            break;

            case 'B':
            gpio_put(BUZZER, true);
            sleep_ms(500);
            gpio_put(BUZZER, false);
            break;

            default:
            break;
        }
        sleep_ms(100);
        }
}
