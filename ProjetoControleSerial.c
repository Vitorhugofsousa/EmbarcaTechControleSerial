#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"


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

//Funcao para ativar o Buzzer por 2 segundos
void tocar_buzzer(){
    gpio_set_function(gpio_buzzer, GPIO_FUNC_PWM);             //Configura pino como saída PWM
    uint numero_slice = pwm_gpio_to_slice_num(gpio_buzzer);    //Obter o slice do PWM

    pwm_set_clkdiv(numero_slice, 125.0);                       //Ajusta a frequencia da onda PWM
    pwm_set_wrap(numero_slice, 255);                           //Define o valor máximo para o contador
    pwm_set_gpio_level(gpio_buzzer, 150);                      //Define a intensidade do som
    pwm_set_enabled(numero_slice, true);                       //Ativar o PWM

    sleep_ms(2000);                                            //Manter o som por 2 segundos

    pwm_set_enabled(numero_slice, false);                      //Desativar o PWM  
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
        printf("Digite um comando (G: Green, B: Blue, R: Red, W: White, Z: Buzzer, O: Off): ");
        tecla = getchar(); //Aguarda comando do terminal

        if(tecla=='Z' || tecla=='z'){          //Caso a tecla enviada for Z
            tocar_buzzer();                   //Chamar funcao para ativar o Buzzer
        }else if(tecla=='T'){
            bootsel();
        }else{
            piscar_leds(tecla);
        }
        sleep_ms(100);         //Pequeno atraso para estabilidade
    }
}
