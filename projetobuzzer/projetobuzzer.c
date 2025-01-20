#include <stdio.h>
#include "pico/stdlib.h"

#define Led_vermelho 20
#define Led_verde 19
#define Led_azul 18
#define Buzzer 21

uint colunas_pin[4] = {4, 3, 2, 1};
uint linhas_pin[4] = {8, 7, 6, 5};

#define L1 8
#define L2 7
#define L3 6
#define L4 5
#define C1 4
#define C2 3
#define C3 2
#define C4 1

//uint linhas[4] = {8, 7, 6, 5};
//uint colunas[4] = {4, 3, 2, 1}; 

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

char ler_teclado(){
    char tecla;
    for (int i = 0; i < 4; i++) {
        gpio_put(L1 + i, 1);

        for (int j = 0; j < 4; j++) {
            if (gpio_get(C1 + j)) {
                sleep_ms(50);

                while (gpio_get(C1 + j)); 

                gpio_put(L1 + i, 0); 

                tecla = key_map[i][j];
            }
        }
        gpio_put(L1 + i, 0);
    }
    return tecla;
}

/*void reset() {
    gpio_put(Led_verde, false);
    gpio_put(Led_azul, false);
    gpio_put(Led_vermelho, false);
}*/

void acionar_Buzzer() {
    printf("Acionando Buzzer\n");
    gpio_put(Buzzer, 1);
    sleep_ms(1000); // 1 segundo
    gpio_put(Buzzer, 0);
    sleep_ms(500); // 0,5 segundos
}

void acionar_Led_vermelho() {
    printf("Acionando Led vermelho\n");
    gpio_put(Led_vermelho, 1);
    sleep_ms(1000); // 1 segundo
    gpio_put(Led_vermelho, 0);
    sleep_ms(500); // 0,5 segundos
}
void acionar_Led_verde() {
    printf("Acionando Led verde\n");
    gpio_put(Led_verde, 1);
    sleep_ms(1000); // 1 segundo
    gpio_put(Led_verde, 0);
    sleep_ms(500); // 0,5 segundos
}

void acionar_Led_azul() {
    printf("Acionando Led azul\n");
    gpio_put(Led_azul, 1);
    sleep_ms(1000); // 1 segundo
    gpio_put(Led_azul, 0);
    sleep_ms(500); // 0,5 segundos
}

void desligar_leds(){
  gpio_put(Led_vermelho, false);
  gpio_put(Led_verde, false);
  gpio_put(Led_azul, false);
  sleep_ms(100);
}

int main(){

    //inicialização dos pinos de led e Buzzer
    stdio_init_all();

    gpio_init(Led_vermelho);
    gpio_set_dir(Led_vermelho, GPIO_OUT);

    gpio_init(Led_verde);
    gpio_set_dir(Led_verde, GPIO_OUT);

    gpio_init(Led_azul);
    gpio_set_dir(Led_azul, GPIO_OUT);

    gpio_init(Buzzer);
    gpio_set_dir(Buzzer, GPIO_OUT);
    gpio_put(Buzzer, 0); //teste

    init_keyboard();
    
    while (true) {
        
        char tecla = ler_teclado();
        printf("\nTecla pressionada: %c\n", tecla);
        switch (tecla){
            case '1': 
            case '4': 
            case '7': 
            case '*':
            gpio_put(Led_verde, true);
            sleep_ms(1000);
            gpio_put(Led_verde, false);
            //break;
            
            case '2': 
            case '5': 
            case '8': 
            case '0':
            gpio_put(Led_azul, true);
            sleep_ms(1000);
            gpio_put(Led_azul, false);
            //break;

            case '3': 
            case '6': 
            case '9': 
            case '#':            
            gpio_put(Led_vermelho, true);
            sleep_ms(1000);
            gpio_put(Led_vermelho, false);
            //break;

            case 'A': 
            case 'C': 
            case 'D':            
            gpio_put(Led_verde, true);
            gpio_put(Led_azul, true);
            gpio_put(Led_vermelho, true);
            sleep_ms(1000);
            gpio_put(Led_verde, false);
            gpio_put(Led_azul, false);
            gpio_put(Led_vermelho, false);
            //break;

            case 'B':
            gpio_put(Buzzer, true);
            sleep_ms(1000);
            gpio_put(Buzzer, false);
            //break;

            default:
            break;
        }
        //sleep_ms(100);
        
    }
}
