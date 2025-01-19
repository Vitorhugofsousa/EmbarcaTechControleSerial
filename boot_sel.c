/* ==========Atenção Guilherme===============
É necessário incluir o cabeçalho "pico/bootrom.h" para que a função reset_usb_boot() seja reconhecida.
Na minha simulação usei o comando "reset" para reiniciar o dispositivo no modo BOOTSEL.

o código abaixo funcionou na minha placa. Deixei o LED azul piscando para ver se o código estava rodando.

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#define LED 12

int main() {
    // Inicializa a UART e configura o baud rate
    stdio_init_all();
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    sleep_ms(2000); // Aguarda inicialização da UART
    printf("UART inicializada. Envie 'reset' para entrar no modo BOOTSEL.\n");

    char buffer[16]; // Buffer para armazenar o comando recebido
    int index = 0;

    while (true) {
        gpio_put(LED, 1); // Acende o LED 
        int c = getchar_timeout_us(100000); // Aguarda entrada por 100ms
        if (c != PICO_ERROR_TIMEOUT) {     // Verifica se houve entrada válida
            if (c >= 32 && c <= 126) {     // Apenas caracteres imprimíveis
                if (index < sizeof(buffer) - 1) {
                    buffer[index++] = c; // Adiciona o caractere ao buffer
                } else {
                    printf("Comando muito longo! Reiniciando buffer.\n");
                    index = 0; // Reseta o buffer em caso de estouro
                }
            } else if (c == '\n' || c == '\r') { // Trata Enter (CR ou LF)
                if (index > 0) { // Processa o comando apenas se houver algo no buffer
                    buffer[index] = '\0'; // Termina a string
                    index = 0;            // Reinicia o buffer

                    // Compara o comando recebido
                    if (strcmp(buffer, "reset") == 0) {
                        printf("Entrando no modo BOOTSEL...\n");
                        reset_usb_boot(0, 0); // Reinicia no modo BOOTSEL
                    } else {
                        printf("Comando desconhecido: %s\n", buffer);
                    }
                }
            } else {
                printf("Caractere não reconhecido: %d\n", c);
            }
        }
                
        gpio_put(LED, 0); // Apaga o LED
        sleep_ms(300);    // Aguarda 300ms
    
    }

    return 0;
}
*/

void funcbootsel() {
    printf("Entrando no modo BOOTSEL...\n");
    reset_usb_boot(0, 0); // Reinicia no modo BOOTSEL
}
