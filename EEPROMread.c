#include <stdlib.h>
#include <avr/io.h>

char EEPROMread(unsigned int address){

	// wait for completion
	while(EECR & (1<<EEPE));

	// set address
	EEAR = address;

	// start EEPROM read
	EECR |= (1<<EERE);

	// return data
	return EEDR;

}

void usart_init(){
	// Enabling receiving and transmitting
	UCSR0B |= (1<<RXEN0);
	UCSR0B |= (1<<TXEN0);

	// Setting to Asynchronous mode
	UCSR0C &= ~(1<<UMSEL01);
	UCSR0C &= ~(1<<UMSEL00);

	// Setting to 8-bit data frame
	UCSR0C &= ~(1<<UCSZ02);
	UCSR0C |= (1<<UCSZ01);
	UCSR0C |= (1<<UCSZ00);

	// Setting to no parity
	UCSR0C &= ~(1<<UPM01);
	UCSR0C &= ~(1<<UPM00);

	// Setting to one stop bit
	UCSR0C &= ~(1<<USBS0);

	// Setting baudrate to 9600bps
	UBRR0 = 103;

}

void usart_send(unsigned char data){
	// Wait till UDR0 is ready
	while (!(UCSR0A & (1<<UDRE0)));

	// Put data into buffer
	UDR0 = data;		

}

int main(){
	
	usart_init();
	char data_rec[256];

	while(1){
		char ch;
		unsigned int i = 0;
		unsigned int count;
		
		
		//receive characters until \r
		while(i<5) {
			ch = EEPROMread(i);
			usart_send(ch);
			i++;
		}


	}

	return 0;
}