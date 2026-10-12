#include "usart.h"

#include <util/delay.h>
#include <stdlib.h>

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
