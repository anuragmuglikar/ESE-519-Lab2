#define F_CPU 16000000L
#define BAUD 9600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART.h"
#include "adc.h"


int buzzAtCount = 0;
unsigned int ticks = 71;
unsigned long timeStart;
unsigned long timeStop;
unsigned long timePeriod;
int overflow = 0;
int rising = 1;
int triggerComplete  = 1;
int freqSelect = 0;
#include "functions.h"


void init(){
	DDRB = 0x22;	//0b00100010; PB5 => Output // Setting the input high on DDR makes the pin OP.
	PORTB = 0b00000001;	//Writing something on the input pins, will take them to internal pull up.
	DDRD = 0b01000100;
	DDRC = 0x00;
	PORTC = 0x01;
	uart_init();
	//init_interrupts();
	adc_init();
}
int main(void)
{
	/* Replace with your application code */
	
	init();
	//generateTriggerPulse();
	
	while (1)
	{
		//pollButton();		//method for polling input pin without interrupts
		//getFreq();
		uint16_t digital = adc_read();
		printf("\n Digital :%u",digital);
	}
}

