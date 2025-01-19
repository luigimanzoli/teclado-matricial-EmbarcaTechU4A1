#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
//define as saidas dos leds e buzzer
const uint led_pin_green = 11;
const uint led_pin_blue  = 12;
const uint led_pin_red   = 13;
const uint buzzer =21;

//define os pinos do teclado com as portas GPIO
uint columns[4] = {4, 3, 2, 1}; 
uint rows[4] = {8, 7, 6, 5};

//mapa de teclas
char KEY_MAP[16] = 
{
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

uint _columns[4];
uint _rows[4];
char _matrix_values[16];
uint all_columns_mask = 0x0;
uint column_mask[4];

void imprimir_binario(int num) {
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}

//inicializa o keypad
void pico_keypad_init(uint columns[4], uint rows[4], char matrix_values[16]) {

    for (int i = 0; i < 16; i++) {
        _matrix_values[i] = matrix_values[i];
    }

    for (int i = 0; i < 4; i++) {

        _columns[i] = columns[i];
        _rows[i] = rows[i];

        gpio_init(_columns[i]);
        gpio_init(_rows[i]);

        gpio_set_dir(_columns[i], GPIO_IN);
        gpio_set_dir(_rows[i], GPIO_OUT);

        gpio_put(_rows[i], 1);

        all_columns_mask = all_columns_mask + (1 << _columns[i]);
        column_mask[i] = 1 << _columns[i];
    }
}

//coleta o caracter pressionado
char pico_keypad_get_key(void) {
    int row;
    uint32_t cols;
    bool pressed = false;

    cols = gpio_get_all();
    cols = cols & all_columns_mask;
    //imprimir_binario(cols);
    
    if (cols == 0x0) {
        return 0;
    }

    for (int j = 0; j < 4; j++) {
        gpio_put(_rows[j], 0);
    }

    for (row = 0; row < 4; row++) {

        gpio_put(_rows[row], 1);

        busy_wait_us(5000);

        cols = gpio_get_all();
        gpio_put(_rows[row], 0);
        cols = cols & all_columns_mask;
        if (cols != 0x0) {
            break;
        }   
    }

    for (int i = 0; i < 4; i++) {
        gpio_put(_rows[i], 1);
    }

    if (cols == column_mask[0]) {
        return (char)_matrix_values[row * 4 + 0];
    }
    else if (cols == column_mask[1]) {
        return (char)_matrix_values[row * 4 + 1];
    }
    if (cols == column_mask[2]) {
        return (char)_matrix_values[row * 4 + 2];
    }
    else if (cols == column_mask[3]) {
        return (char)_matrix_values[row * 4 + 3];
    }
    else {
        return 0;
    }
}

void desligar_leds(){
  gpio_put(led_pin_green, false);
  gpio_put(led_pin_blue, false);
  gpio_put(led_pin_red, false);
  sleep_ms(100);
}

void ligar_verde(){
  printf("VERDE LIGADO \n");
  gpio_put(led_pin_green, true);
  sleep_ms(100);
}

void ligar_azul(){
  printf("AZUL LIGADO \n");
  gpio_put(led_pin_blue, true);
  sleep_ms(100);
}

void ligar_vermelho(){
  printf("VERMELHO LIGADO \n");
  gpio_put(led_pin_red, true);
  sleep_ms(100);
}


void ativar_buzzer(){
  printf("BUZZER ATIVADO \n");
  gpio_put(buzzer, true);
  sleep_ms(2000);
  gpio_put(buzzer, false);
}

void inicializacao(){
  gpio_init(led_pin_green);
  gpio_set_dir(led_pin_green, GPIO_OUT);
  gpio_init(led_pin_blue);
  gpio_set_dir(led_pin_blue, GPIO_OUT);
  gpio_init(led_pin_red);
  gpio_set_dir(led_pin_red, GPIO_OUT);
  gpio_init(buzzer);
  gpio_set_dir(buzzer, GPIO_OUT);
  stdio_init_all();
}


//função principal
int main() {
    inicializacao();
    pico_keypad_init(columns, rows, KEY_MAP);
    char caracter_press;

    while (true) {
        caracter_press = pico_keypad_get_key();
        printf("\nTecla pressionada: %c\n", caracter_press);

        //Avaliação de caractere para o LED
        if(caracter_press=='A')
        {
           ligar_azul();
           desligar_leds();
        }else if(caracter_press=='B')
        {
          ligar_verde();
          desligar_leds();
        }
        else if(caracter_press=='C'){
          ligar_vermelho();
          desligar_leds();
        }
        else if(caracter_press=='D'){
          ativar_buzzer();
        }
        else{
          continue;
        }
    }
}

