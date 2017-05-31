#include <stdlib.h>
#include <avr/io.h>

void EEPROMwrite(unsigned int address, char data){

	// wait for completion of previous
	while(EECR & (1<<EEPE));

	// setup address and data
	EEAR = address;
	EEDR = data;

	// write logical 1 to EEMPE
	EECR |= (1<<EEMPE);

	// start EEPROM write
	EECR |= (1<<EEPE);

}

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

unsigned char usart_receive(){
	// Wait till data is received
	while (!(UCSR0A & (1<<RXC0)));

	// Get the data
	return UDR0;
}

int main(){
	
	usart_init();
	char data_rec[256];

	while(1){
		char ch;
		unsigned int i = 0;
		unsigned int count;
		
		
		//receive characters until \r
		while((ch = usart_receive()) != '\r') {
			data_rec[i] = ch;
			EEPROMwrite(i,data_rec[i]);	// write to EEPROM
			i++;
		}
		count = i;

		


	}

	return 0;
}