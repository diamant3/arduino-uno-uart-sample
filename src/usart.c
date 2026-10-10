#define F_CPU 16000000UL // 8 MHz Clock Speed
#define BAUD 9600UL
#define UBRRN ((F_CPU / (BAUD * 16UL)) - 1)

#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>

void uart_init(unsigned int ubrr) {
    // set baud rate register
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // enable tx
    UCSR0B = (1 << TXEN0);

    // set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    // Put data into buffer and then sends the data
    UDR0 = data;
}

void uart_print(const char* str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

int main(void) {
    char buf[8];

    uart_init(UBRRN);

    while (1) {
        // send the message
        uart_print("Hello from ATmega328P\r\n");

        for (int i = 1; i <= 10; i++) {
            itoa(i, buf, 10);
            uart_print("Counter: ");
            uart_print(buf);
            uart_print("\r\n");
        }

        // Wait 1 second
        _delay_ms(1000);

        // Clear screen
        uart_print("\x1B[2J\x1B[H");
    }

    return 0;
}
