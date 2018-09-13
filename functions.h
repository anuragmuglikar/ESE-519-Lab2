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
	TCCR0B |= (1 << CS01);	// timer with no pre-scaling
	TCNT0 = 0;		// start counter
	TIMSK0 = 0b00000001; //Enable overflow interrupt.
}

void playMusic(){
		PORTD ^= (1 << 6);
		//TCNT0 = 0;            // reset counter
		
}

void init_interrupts(){
		
	TCCR1B |= 0b00000001; //setting the prescaler to 1.
	TCCR1B |= 0b00000000; //Enabling ICES1 (7) to detect a falling edge
	TIMSK1 = 0b00100000; //Enable ICEI pin.
	sei();				// Enable global interrupt

}

ISR(TIMER1_CAPT_vect){
	//PORTB ^= 1 << 5;
	//TCCR1B ^= 1 << 6;	//setting ICES Pin to detect a rising edge so that the same pin can be toggle back when button is released.
}

ISR(TIMER0_OVF_vect){
	buzzAtCount ++;
	if(buzzAtCount == 80){
		buzzAtCount = 0;
		playMusic();			//method for buzzing the buzzer.
	}
	TIFR0 = 1 << 0;
	TCNT0 = 0;
}