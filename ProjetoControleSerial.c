#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"


#define gpio_buzzer 21
#define gpio_led_green 11
#define gpio_led_blue 12
#define gpio_led_red 13

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

// funcao para controlar os leds
void piscar_leds(char tecla)
{
    desligar_leds(); // Garante que apenas um LED estará ligado
    switch (tecla)
    {
    case 1: // LED Verde
    
        break;
    case 2: // LED Azul

        break;
    case 3: // LED Vermelho

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

void desligar_leds()
{
    // Desliga os leds
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
    return 0; // Comando inválido
}

void bootsel()
{
    // Verifica se o botão de seleção foi pressionado
}

int main()
{
    stdio_init_all();
    inicializa_pinos();

    char entrada[20];

    printf("Digite um comando (GREEN, BLUE, RED, WHITE, BUZZER, OFF): \n");

    while (1)
    {
        // Recebe comandos via UART
        scanf("%19s", entrada); // Lê o comando enviado pelo monitor serial

        int comando = mapear_comando(entrada); // Converte o comando para um valor numérico

        switch (comando)
        {
        case 1:                   // GREEN
        case 2:                   // BLUE
        case 3:                   // RED
        case 4:                   // WHITE
            piscar_leds(comando); // Controla os LEDs
            printf("ON: %s\n", entrada);
            break;
        case 5:             // BUZZER
            tocar_buzzer(); // Ativa o buzzer
            printf("ON: %s\n", entrada);
            break;
        case 6:              // OFF
            desligar_leds(); // Desliga todos os LEDs
            printf("LEDS: %s\n", entrada);
            break;
        default:
            printf("Comando inválido\n");
        }
        sleep_ms(100); // Pequeno atraso para estabilidade
    }
}
