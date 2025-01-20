#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pwm.h"

#define gpio_buzzer 21
#define gpio_led_green 11
#define gpio_led_blue 12
#define gpio_led_red 13

//Função para inicializar os pinos de controle dos LEDs e do Buzzer
void inicializa_pinos()
{
    gpio_init(gpio_led_green);
    gpio_set_dir(gpio_led_green, GPIO_OUT);

    gpio_init(gpio_led_blue);
    gpio_set_dir(gpio_led_blue, GPIO_OUT);

    gpio_init(gpio_led_red);
    gpio_set_dir(gpio_led_red, GPIO_OUT);

    gpio_init(gpio_buzzer);
    gpio_set_dir(gpio_buzzer, GPIO_OUT);
}

//Função para desligar todos os LEDS
void desligar_leds()
{
    printf("Apagando todos os LEDs...\n");
    gpio_put(gpio_led_blue, 0);
    gpio_put(gpio_led_green, 0);
    gpio_put(gpio_led_red, 0);
    printf("Todos LEDs foram apagados\n");
}

// Função para controlar os leds
void piscar_leds(char tecla)
{
    desligar_leds(); // Garante que apenas um LED estará ligado
    switch (tecla)
    {
    case 1: // LED Verde
        printf("Ligado LED verde...\n");
        gpio_put(gpio_led_red, false);
        gpio_put(gpio_led_green, true);
        gpio_put(gpio_led_blue, false);
        printf("LED verde ligado\n");
        break;
    case 2: // LED Azul
        printf("Ligado LED azul...\n");
        gpio_put(gpio_led_red, false);
        gpio_put(gpio_led_green, false);
        gpio_put(gpio_led_blue, true);
        printf("LED azul ligado\n");
        break;
    case 3: // LED Vermelho
        printf("Ligado LED vermelho...\n");
        gpio_put(gpio_led_red, true);
        gpio_put(gpio_led_green, false);
        gpio_put(gpio_led_blue, false);
        printf("LED vermelho ligado\n");
        break;
    case 4: // Todos os LEDs
        gpio_put(gpio_led_red, true);
        gpio_put(gpio_led_green, true);
        gpio_put(gpio_led_blue, true);
        break;
    default:
        printf("Comando inválido para LEDs\n");
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

// Função auxiliar para mapear strings em valores inteiros
int mapear_comando(const char *comando)
{
    if (strcmp(comando, "GREEN") == 0)
        return 1;
    if (strcmp(comando, "BLUE") == 0)
        return 2;
    if (strcmp(comando, "RED") == 0)
        return 3;
    if (strcmp(comando, "WHITE") == 0)
        return 4;
    if (strcmp(comando, "BUZZER") == 0)
        return 5;
    if (strcmp(comando, "OFF") == 0)
        return 6;
    if (strcmp(comando, "BOOTSEL") == 0)
        return 7;
    return 0; // Comando inválido
}

// Função para entrar no modo BOOTSEL
void bootsel()
{
    printf("Entrando no modo BOOTSEL...\n");
    reset_usb_boot(0, 0); // Reinicia no modo BOOTSEL
}

int main()
{
    stdio_init_all();
    inicializa_pinos();

    char entrada[20];

    printf("Digite um comando (GREEN, BLUE, RED, WHITE, BUZZER, OFF, BOOTSEL): \n");

    while (1)
    {
        // Recebe comandos via UART
        scanf("%19s", entrada); // Lê o comando enviado pelo monitor serial

        int comando = mapear_comando(entrada); // Converte o comando para um valor numérico

        switch (comando)
        {
        case 1:                             // GREEN
            piscar_leds(comando);
            printf("ON: %s\n", entrada);
        case 2:                             // BLUE
            piscar_leds(comando);
            printf("ON: %s\n", entrada);
        case 3:                             // RED
            piscar_leds(comando);
            printf("ON: %s\n", entrada);
        case 4:                             // WHITE
            piscar_leds(comando);           // Controla os LEDs
            printf("ON: %s\n", entrada);
            break;
        case 5:                             // BUZZER
            tocar_buzzer();                 // Ativa o buzzer
            printf("ON: %s\n", entrada);
            break;
        case 6:                             // OFF
            desligar_leds();                // Desliga todos os LEDs
            printf("LEDS: %s\n", entrada);
            break;
        case 7:                             // BOOTSEL
            bootsel();
            break;
        default:
            printf("Comando inválido\n");
        }
        sleep_ms(100); // Pequeno atraso para estabilidade
    }
}