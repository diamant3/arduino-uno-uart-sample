#define F_CPU 16000000UL // 16 MHz Clock Speed
#define BAUD 115200UL
#define UBRRN ((F_CPU / (BAUD * 8UL)) - 1)

void uart_init(unsigned int ubrr);
// void uart_transmit(char data);
void uart_print(const char* str);