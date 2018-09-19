#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


int buzzAtCount = 0;
unsigned int ticks = 71;
#include "functions.h"


void init(){
	DDRB = 0x22;	//0b00100010; PB5 => Output // Setting the input high on DDR makes the pin OP.
	PORTB = 0b00000001;	//Writing something on the input pins, will take them to internal pull up.
	DDRD = 0b01000100;
	//timer0_init();
	//init_interrupts();
}
int main(void)
{
	/* Replace with your application code */
	init();
	generateTriggerPulse();
	while (1)
	{
		//pollButton();		//method for polling input pin without interrupts

		
	}
}

