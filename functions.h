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

void playMusic(){
		PORTD ^= (1 << 6);
		//TCNT0 = 0;            // reset counter
		
}

void init_interrupts(){
	
	// This section for wave generation using timers
	/*TCCR0A |= 0b01000000;	//compare mode
	TCCR0B |= 0b00000100;	//prescale 256
	TIMSK0 |= 0b00000010; //Enable ICEI pin.
	OCR0A = TCNT0 + ticks; */
	
	//Wave generation with CTC Mode
	/*
	TCCR0A = 0b01000010; //CTC Mode
	TCCR0B = 0b10000100;
	TIMSK0 = 0b00000011; 
	TCNT0 = 0;
	OCR0A = TCNT0 + ticks;
	sei();				// Enable global interrupt
*/
}

void generateTriggerPulse(){
	//TCCR1B = 0b00000010; //setting the prescaler to 1.
	cli();
	TCCR1A = 0b00000000; //CTC Mode
	TCCR1B = 0b00000010; //prescale 8
	
	overflow = 0;
	TCNT1 = 0;
	OCR1A = 10;
	TIMSK1 = 0b000000010; //Enable ICEI pin interrupt.
	PORTB = 0b00000010; 
	sei();
}

void findRange(){
	
}

//unused func
void enablePulseCapture(){
	TCCR1A = 0b00000000; 
	TCCR1B = 0b01000001;
	TCNT1 = 0;
	rising = 1;
	TIMSK1 |= 0b001000000; //Enable ICEI pin interrupt.
	
}

void getFreq(){
timePeriod = timeStop - timeStart;
if(timeStop < timeStart){
	overflow--;
	timePeriod = (overflow * 0.0327675) + (timeStart- timeStop)*0.0000005;
	}else{
	timePeriod = (overflow * 0.0327675) + timePeriod;
}
printf("\n Period ==> %d", timePeriod);
}

ISR(TIMER1_CAPT_vect){
	if(rising){
		PORTB |= (1 << 5);
		timeStart =	(TCNT1H << 8) | (TCNT1L & 0xff);
		rising = 0;
		TCCR1B ^= 1 << 6;	//setting ICES Pin to detect a falling edge so that the same pin can be toggle back when button is released.
	}else{
		TIMSK1 = 0x00;
		rising = 1;
		TCCR1B = 0x00;
		PORTB &= (0 << 5);
		timeStart =	(TCNT1H << 8) | (TCNT1L & 0xff);
		generateTriggerPulse();
	}
	
	
}

ISR(TIMER1_COMPA_vect){
	//PORTB |= (1 << 5);
	//printf("G T P INT \n");
	TCNT1 = 0;
	OCR1A = 10;
	cli();
	PORTB = 0b00000000; 
	TCCR1B = 0b01000010;
	rising = 1;
	
	TIMSK1 = 0b00100000; //Enable ICEI pin interrupt.
	sei();
	
}


ISR(TIMER1_OVF_vect){
	overflow++;
}

ISR(TIMER0_COMPA_vect){
	PORTD ^= 1 << 6;
}