/*
 * adc.h
 *
 * Created: 20-09-2018 18:27:06
 *  Author: DELL
 */ 
adc_init(){
	ADMUX = 0b01000000;
	ADCSRA = 0b00000111;
}

uint16_t adc_read(){
	ADCSRA |= 0b01000000;
	ADCSRA |= 0b10000000;
	while (ADCSRA & (1<<ADSC));
	return ADC;
}