#include <avr/io.h>
#include <avr/interrupt.h>
//compare value used to generate a ~4kHz oscillation of the LED array
uint8_t IRLedFlashSpeed = 30;

//global variable used to store whether the LED array is currently on/off
uint8_t LEDSwitch;

//////////////////////////////////////////////////////////////////////////
//////////////////////// Prototype methods ///////////////////////////////
//////////////////////////////////////////////////////////////////////////

//Initialize data registers and compare values for LED control. Uses the same timer (timer0) as the main
// timer function getClockTicks but compares using the second compare register
void initLED(void);


//turn the LED array on off based on a boolean flag
void toggleLED(uint8_t toggle);

//check to see if the LED array is currently on/off
uint8_t LEDPowerCheck(void);


//////////////////////////////////////////////////////////////////////////
//////////////////////// Method definitions //////////////////////////////
//////////////////////////////////////////////////////////////////////////

void initLED(void){
	//set compare value to get desired frequency
	OCR0B = IRLedFlashSpeed;
	
	//enable interrupt on output compare match for register OCRB
	TIMSK0 |= (1<< OCIE0B);
	
	
	//clear interrupt flag for ocr0b
	TIFR0 &= (1 << OCF0B);
}


// Toggle the LED array on/off using a boolean flag (0/1)
void toggleLED(uint8_t toggle){
	if (toggle == 1){
		LEDSwitch = 1;
		//set bit 2
		DDRB |= (1 << 2);
	}
	else if (toggle == 0){
		LEDSwitch = 0;
		//clear bit 2
		DDRB &= ~(1 << 2);
	}
}


//check to see if the LED array is currently powered
uint8_t LEDPowerCheck(void){
	return LEDSwitch;
}


//ISR to flash the LED's at ~ 400kHz when the LED array is toggled ON
ISR(TIMER0_COMPB_vect)
{
	//if the LED toggle bit is set, turn on/off the LED array
	if (DDRB & (1 <<2)){
		PORTB ^= (1 << 2);		
	}
	//else do nothing
	else{;}
}
/*
void timer1_init()
{
	// set up timer with prescaler = 64 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = IRLedFlashSpeed;
}
*/
/*
int main(void)
{
	// connect led to pin PC0
	DDRC |= (1 << 0);
	
	// initialize timer
	timer1_init();
	
	// loop forever
	while(1)
	{
		// check whether the flag bit is set
		// if set, it means that there has been a compare match
		// and the timer has been cleared
		// use this opportunity to toggle the led
		if (TIFR1 & (1 << OCF1A)) // NOTE: '>=' used instead of '=='
		{
			PORTC ^= (1 << 0); // toggles the led
		}
		
		// wait! we are not done yet!
		// clear the flag bit manually since there is no ISR to execute
		// clear it by writing '1' to it (as per the datasheet)
		TIFR1 |= (1 << OCF1A);
		
		// yeah, now we are done!
	}
}
*/