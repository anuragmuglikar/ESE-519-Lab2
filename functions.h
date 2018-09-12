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
}

void letsBuzz(){
	if (TCNT0 >= 250)
	{
		PORTD ^= (1 << 6);
		TCNT0 = 0;            // reset counter
	}
}

void 