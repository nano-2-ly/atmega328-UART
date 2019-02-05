#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#define _BV(bit) (1<<(bit))

void UART_INIT(void){
	UCSR0A |= _BV(U2X0);
	
	UBRR0H = 0x00;
	UBRR0L = 207;
	
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);

}

unsigned char UART_receive(void){
	while( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

unsigned UART_transmit(unsigned char data){
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

int main(int argc, char *argv[])
{
	unsigned char data;
	
	UART_INIT();
	while(1){
		data = UART_receive();
		UART_transmit(data);
	}
	return 0 ;
	
}