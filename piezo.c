/*
 * Piezo.c
 *
 * Created: 15/10/2015 11:40:15 AM
 *  Author: Andrew Osborne
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"

//middle C: 261.6 Hz.
void init_piezo(void){
	DDRD |= (1 << 3);
}
void buzz(uint32_t freq, uint32_t duration){
	uint32_t start_buzz = getClockTicks();
	uint32_t end_buzz = start_buzz + duration;
	
	uint32_t current_time = start_buzz;
	PORTD |= (0 << 3);
	while(getClockTicks() < end_buzz){	
		if (getClockTicks() > current_time + freq){
			PORTD ^= (1 << 3);		
			current_time = getClockTicks();
		}
	PORTD |= (0 << 3);	
	}
	
}

// TEST CODE
// How to use in main function:	
// 	int main(void){
// 		initTimer0();
// 		
// 		init_piezo();
// 		uint32_t frequency = 1;
// 		uint32_t duration = 500;
// 		buzz(frequency, duration);
// 
// 	}
