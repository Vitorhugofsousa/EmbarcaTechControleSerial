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

//funcao para controlar os leds
void piscar_leds(char tecla){
    switch(tecla){  //estrutura switch para verificar qual tecla foi pressionada e qual ação tomar
        case 'G':   //tecla G -> led green

        break;
        default: 
        
    }
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

    char tecla;

    while(1){
        //Recebe comandos via UART
        printf("Digite um comando (G: Green, B: Blue, R: Red, W: White, T: Buzzer, O: Off): ");
        tecla = getchar(); //Aguarda comando do terminal

        if(tecla=='B'){       
            tocar_buzzer();
        }else if(tecla=='T'){
            bootsel();
        }else{
            piscar_leds(tecla);
        }
        sleep_ms(100);
    }
}
