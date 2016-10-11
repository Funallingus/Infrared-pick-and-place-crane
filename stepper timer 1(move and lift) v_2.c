/*
	
	Author: Johanna Cisneros
*/


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

//Set the initial position for both motors
uint8_t step1 = 0;
uint8_t step2 = 0;

//Set motor ID = 1. (lifting motor)
uint8_t motorID = 1;
uint16_t defaultStep = 100;

////#########################################################
//Prototype functions
// Initialize motor control timer and data direction register
void initMotorTimer(void);

//start the timer for motor step control
void motorStart (void);

//stop the timer fir motor step control
void motorStop (void);

//move one step clockwise
void moveClockwise (void);

//move one step counter clockwise
void moveCounterclockwise (void);

//Initialize the lift motor at startup so that it in not lowered all the way
void initLiftMotor(void);

//change the motor that is being controlled (0 for driving motor, 1 for lifting motor)
void selectMotor (int motorSelect);

//set the speed that the motor is stepping at
void changeSpeed (int speed);

//function that takes a direction and the number of steps to move and then turns the drive motor for the required number of steps
void motorSearch (uint8_t direction, uint16_t stepsToTake);

//lower the lifting motor so that it makes contact with the block then lift the block up so that it can be moved to an IR beacon
void pickupBlock (void);

//lift the block slightly to physically separate it from the magnets then return the end effector to its original position
void dropBlock (void);

///##############################################################


void initMotorTimer(void){
	//set Port D to outputs
	DDRD |= 0xF7;
	
	//register compare value
	OCR1A = 1000; 
	
	//Start timer
	TCCR1B |= ((1<<WGM12)|(1<<CS11)|(1<<CS10));
	
}


void moveClockwise (void){
	//wait until OCF1A flag is set before you move on
	while(!(TIFR1 & (1<<OCF1A))){
		//do nothing
		;
	}
	//once OCF1A flag set step clockwise based on current step position
	//Moving motor-->MotorID = 0
	//Lifting motor-->MotorID = 1
	switch (step1){
		case 0:
		if (motorID == 0){
			//Moving motor
			PORTD = 1; 
		}else{
			//Lifting motor
			PORTD = 4;
		}
		step1 ++;
		break;
		
		case 1:
		if (motorID == 0){
			//Moving motor
			PORTD = 0;
		}else{
			//Lifting motor
			PORTD = 0;
		}
		step1 ++;
		break;
		
		case 2:
		if (motorID == 0){
			//Moving motor
			PORTD = 2;
		}else{
			//Lifting motor
			PORTD = 16;
		}
		step1 ++;
		break;
		
		case 3:
		if (motorID == 0){
			//Moving motor
			PORTD = 3;
		}else{
			//Lifting motor
			PORTD = 20;
		}
		step1 = 0;
		break;
	}
	//clear the timer interrupt flag register
	TIFR1 = (1<<OCF1A);
}

void moveCounterclockwise (void){
	//wait until OCF1A flag is set before you move on
	while(!(TIFR1 & (1<<OCF1A))){
		//do nothing
		;
	}
	//once OCF1A flag set step counterclockwise based on current step position
	//Moving motor-->MotorID = 0
	//Lifting motor-->MotorID = 1
	switch (step2){
		case 0:
		if (motorID == 0){
			//Moving motor
			PORTD = 3;
		}else{
			//Lifting motor
			PORTD = 20;
		}
		step2++;
		break;
		
		case 1:
		if (motorID == 0){
			//Moving motor
			PORTD = 2;
		}else{
			//Lifting motor
			PORTD = 16;
		}
		step2 ++;
		break;
		
		case 2:
		if (motorID == 0){
			//Moving motor
			PORTD = 0;
		}else{
			//Lifting motor
			PORTD =0;
		}
		step2 ++;
		break;
		
		case 3:
		if (motorID == 0){
			//Moving motor
			PORTD = 1;
		}else{
			//Lifting motor
			PORTD = 4;
		}
		step2 = 0;
		break;
	}
	//clear the Timer interrupt flag
	TIFR1 = (1<<OCF1A);
}

void selectMotor (int motorSelect){
	//This function select the motor to be used
	//Moving motor-->MotorID = 0
	//Lifting motor-->MotorID = 1
	if (motorSelect == 1){
		motorID = 1;
		}
	else if (motorSelect == 0){
		motorID = 0;
	}
}


void changeSpeed (int speed){
	//This function changes the speed at which the motors move/lift
	if (speed == 2){
		OCR1A = 1200;
	}
	else if (speed == 1){
		OCR1A = 500;
	}
}


void motorSearch (uint8_t direction, uint16_t stepsToTake){
	//motor moves a given number of steps
	//direction is 0, to move forwards CLOCKWISE
	//direction is 1, to move backwards COUNTERCLOCKWISE
	if (direction == 0)
	{
		//Move forwards
		for(uint16_t i = 0; i < stepsToTake; i++){
			moveClockwise();
		}
	}else{
		//Move backwards
		for(uint16_t i = 0; i < stepsToTake; i++){
			moveCounterclockwise();
		}
	}
}

void motorStop (void){
	//Turn off the timer
	TCCR1B ^= ((1<<CS11)|(1<<CS10));
}

void motorStart (void) {
	//Start the timer
	TCCR1B |= ((1<<WGM12)|(1<<CS11)|(1<<CS10));
	TCNT1 = 0;
}

void pickupBlock (void){
	/*  PICK UP BLOCK */
	
	//switch to lifting motor
	selectMotor(1); //now we are in the lifting motor
	//changeSpeed(); //constant speed for lifting
	motorSearch(1, 60); //"drop end effector"
	_delay_ms(500);
	motorSearch(0,340); //lift a block
	selectMotor(0);//switch back to moving motor
}

void dropBlock (void){
	/*  DROP THE BLOCK IN THE BIN */
	
	///switch to lifting motor
	selectMotor(1); //now we are in lifting motor
	//changeSpeed(); //speed for lifting
	motorSearch(0,60); //lift the block "extra distance" so it drops
	//The BLOCK HAS BEEN DROPPED
	_delay_ms(400);
	//Go back to initial position of the end effector
	motorSearch(1,45);
	selectMotor(0);//switch back to moving motor	
}

void initLiftMotor(void){
	selectMotor(1);
	//Lift the end effector to its initial position. Ready to start searching for blocks
	motorSearch(0, 65);
	selectMotor(0);
}
