
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "serialio.h"
#include "sensor.h"


#define SYSCLK 8000000L


void initSensor(void){
	// Set up ADC - AVCC reference, right adjust
	// Input selection doesn't matter yet - we'll swap this around in the while
	// loop below.
	//guarantees that REFS0 and REFS1 are zero (external reference voltage)
	ADMUX = 0;
	
	// Turn on the ADC (but don't start a conversion yet). Choose a clock
	// divider of 64. (The ADC clock must be somewhere
	// between 50kHz and 200kHz. We will divide our 8MHz clock by 64
	// to give us 125kHz.)
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}


//not yet implemented
uint8_t ditialReadSensor(void){
	return 1;
}


//start an ADC of the sensor you are interested in and then return the value of the reading
uint16_t analogReadSensor(uint8_t sensor){
	uint16_t reading;
	//save interrupt status then disable
	uint8_t interrupts_enabled = bit_is_set(SREG, SREG_I);
	cli();
	//if sensor is set to one, read ADC0
	if (sensor == 1){
		ADMUX = 0;
	}
	//if sensor is set to 2, read ADC1
	else if (sensor == 2){
		ADMUX &= ~(1 << 1);
		ADMUX |= (1 << 0);
	}
	//if sensor is set to 3, read ADC2
	else if (sensor == 3){
		ADMUX &= ~(1 << 0);
		ADMUX |= (1 << 1);
	}

	// Start the ADC conversion
	ADCSRA |= (1<<ADSC);
			
	while(ADCSRA & (1<<ADSC)) {
		; /* Wait until conversion finished */
	}
	reading = ADC;
	//restore interrupt register
	if(interrupts_enabled) {
		sei();
	}
	//return the ADC value
	return reading;
}