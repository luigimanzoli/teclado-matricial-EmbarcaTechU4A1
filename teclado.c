#include <stdio.h>
#include "pico/stdlib.h"


#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define C1 5
#define C2 6
#define C3 7
#define C4 8

#define RLED_PIN 11
#define GLED_PIN 12
#define BLED_PIN 13

#define BUZZER 28

// Inicializa os pinos dos LEDs
void init_led() {
    gpio_init(RLED_PIN);
    gpio_set_dir(RLED_PIN, GPIO_OUT);
    gpio_put(RLED_PIN, 0);

    gpio_init(GLED_PIN);
    gpio_set_dir(GLED_PIN, GPIO_OUT);
    gpio_put(GLED_PIN, 0);

    gpio_init(BLED_PIN);
    gpio_set_dir(BLED_PIN, GPIO_OUT);
    gpio_put(BLED_PIN, 0);
}

void get_led(bool R, bool G, bool B) {
    gpio_put(RLED_PIN, R);
    gpio_put(GLED_PIN, G);
    gpio_put(BLED_PIN, B);
}

// Mapeamento das teclas em uma matriz 4x4
char teclas[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void init_teclado() {
    for (int i = 0; i < 4; i++){

      gpio_init(R1 + i);
      gpio_set_dir(R1 + i, GPIO_OUT);
      gpio_put(R1 + i, 0);

      gpio_init(C1 + i);
      gpio_set_dir(C1 + i, GPIO_IN);
      gpio_pull_down(C1 + i);

    }}

char leitura_teclado() {
    for (int row = 0; row < 4; row++) {
        gpio_put(R1 + row, 1);

        for (int col = 0; col < 4; col++) {
            if (gpio_get(C1 + col)) {
                sleep_ms(100);
                while (gpio_get(C1 + col)){
                  gpio_put(R1 + row, 0);
                }
                return teclas[row][col];
            }
        }
        gpio_put(R1 + row, 0);
    }
    return 0;
}


int main() {
    stdio_init_all();
    init_teclado();
    init_led();

    while (1) {
        char key = leitura_teclado();

        if (key == 0){
          printf("Tecle algo!\n");
        }
        else if (key) {

          printf("Tecla pressionada: %c\n", key);

          if (key == 'A'){
            get_led(1,0,0);
          }
          else if (key == 'B'){
            get_led(0,1,0);
          }
        }
        sleep_ms(100);
    }
}