#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "functions.h"


void init(){
	DDRB = 0x20;	//0b00100000; PB5 => Output // Setting the input high on DDR makes the pin OP.
	PORTB = 0x01;	//Writing something on the input pins, will take them to internal pull up.
	DDRD = 0b01000000;
	PORTB |= 0b00000000;
	timer0_init();
	init_interrupts();
}
int main(void)
{
	/* Replace with your application code */
	init();
	while (1)
	{
		pollButton();		//method for polling input pin without interrupts
		playMusic();			//method for buzzing the buzzer.
		
	}
}

