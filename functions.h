/*
 * functions.c
 *
 * Created: 11-09-2018 22:16:30
 *  Author: Anurag Muglikar
 */ 

void pollButton(){
	if(!(PINB & 0x01)){			//true if input PB0 goes low.
			PORTB |= 0x20;			//0b00100000; sets high output
			}else{
			PORTB &= 0b11011111;	// sets output low. preserving other pins.
		}
}

void timer0_init()
{
	//TCCR0B |= (1 << CS01);	// timer with no pre-scaling
	//TCNT0 = 0;		// start counter
	//TIMSK0 = 0b00000001; //Enable overflow interrupt.
}

void playMusic(){
		PORTD ^= (1 << 6);
		//TCNT0 = 0;            // reset counter
		
}

void init_interrupts(){
		
	TCCR1B |= 0b00000001; //setting the prescaler to 1.
	TCCR1B |= 0b10000000; //Enabling ICES1 (7) to detect a falling edge
	TIMSK1 = 0b000000010; //Enable ICEI pin interrupt.
	
	// This section for wave generation using timers
	/*TCCR0A |= 0b01000000;	//compare mode
	TCCR0B |= 0b00000100;	//prescale 256
	TIMSK0 |= 0b00000010; //Enable ICEI pin.
	OCR0A = TCNT0 + ticks; */
	
	//Wave generation with CTC Mode
	TCCR0A = 0b01000010; //CTC Mode
	TCCR0B = 0b10000100;
	TIMSK0 = 0x00; //No Interrupts
	TCNT0 = 0;
	OCR0A = TCNT0 + ticks;
	//sei();				// Enable global interrupt

}

void generateTriggerPulse(){
	TCCR1B = 0b00000001; //setting the prescaler to 1.
	TCCR1A = 0b01000010; //CTC Mode
	TCCR1B |= 0b01000000;
	PORTB |= 0b00000010; 
	TCNT1 = 0;
	sei();
	OCR1A = TCNT1 + 40;
	TIMSK1 = 0b000000010; //Enable ICEI pin interrupt.
	
}

void findRange(){
	
}






ISR(TIMER1_CAPT_vect){
	
	TCCR1B ^= 1 << 6;	//setting ICES Pin to detect a rising edge so that the same pin can be toggle back when button is released.
}

ISR(TIMER0_COMPA_vect){
	OCR0A += ticks;
	PORTD ^= 1 << 6;
	PORTB ^= 1 << 5;
	//TCCR0A ^= 1 << 6;	//setting ICES Pin to detect a rising edge so that the same pin can be toggle back when button is released.
}

/*ISR(TIMER0_OVF_vect){
	buzzAtCount ++;
	if(buzzAtCount == 80){
		buzzAtCount = 0;
		playMusic();			//method for buzzing the buzzer.
	}
	//TIFR0 = 1 << 0;
	TCNT0 = 0;
}*/