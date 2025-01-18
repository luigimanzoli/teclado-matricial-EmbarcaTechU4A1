#include <stdio.h>
#include "pico/stdlib.h"

#define Led_vermelho 20;
#define Led_verde 19;
#define Led_azul 18;
#define Buzzer 21;


int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
