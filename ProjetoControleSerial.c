#include <stdio.h>
#include "pico/stdlib.h"

#define gpio_buzzer 21
#define gpio_led_green 11
#define gpio_led_blue 12
#define gpio_led_red 13

void inicializa_pinos(){
    gpio_init(gpio_led_green);
    gpio_set_dir(gpio_led_green, GPIO_OUT);

    gpio_init(gpio_led_blue);
    gpio_set_dir(gpio_led_blue, GPIO_OUT);

    gpio_init(gpio_led_red);
    gpio_set_dir(gpio_led_red, GPIO_OUT);

    gpio_init(gpio_buzzer);
    gpio_set_dir(gpio_buzzer, GPIO_OUT);
}

void piscar_leds(int gpio_led){
    // Liga o led
}

void tocar_buzzer(){
    // Liga o buzzer
}

void desligar_leds(){
    // Desliga os leds
}

void leitura_serial(){
    // Lê a serial
}

void bootsel(){
    // Verifica se o botão de seleção foi pressionado
}

int main()
{
    stdio_init_all();
    inicializa_pinos();

    while(1){
        //Aguardando Código
        sleep_ms(1000);
    }
}
