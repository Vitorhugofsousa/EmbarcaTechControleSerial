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
void piscar_leds(char tecla) {
    desligar_leds(); // Garante que apenas um LED estará ligado
    switch(tecla) {
        case 'G':   // LED Verde
            
            break;
        case 'B':   // LED Azul
            
            break;
        case 'R':   // LED Vermelho
            
            break;
        case 'W':   // Todos os LEDs
            
            break;
        default:
            printf("Comando inválido para LEDs\n");
    }
}

//Funcao para ativar o Buzzer por 2 segundos
void tocar_buzzer(){
    gpio_put(gpio_buzzer, true);      //Ligar o buzzer
    sleep_ms(2000);                  //Buuzer ativo por 2 segundos
    gpio_put(gpio_buzzer, false);   //Desativar buzzer
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
        
        switch(tecla) {
            case 'G':
            case 'B':
            case 'R':
            case 'W':
                piscar_leds(tecla); // Controla os LEDs
                break;
            case 'T':
                tocar_buzzer();     // Ativa o buzzer
                break;
            case 'O':
                desligar_leds();    // Desliga todos os LEDs
                break;
            default:
                printf("Comando inválido\n");
        }
        sleep_ms(100);         //Pequeno atraso para estabilidade
    }
}
