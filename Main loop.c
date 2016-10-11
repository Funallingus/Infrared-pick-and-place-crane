/*
 *Main loop.c
 *
 * Created: 30/09/2015 8:16:56 AM
 *  Author: Lachlan 
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "serialio.h"
#include "sensor.h"
#include "LED control.h"
//#include "stepper motor.h"
#include "stepper timer 1(move and lift) v_2.h"
#include "piezo.h"


#define F_CPU 8000000UL

uint16_t beaconThreshold = 650;
uint16_t beamLength = 1900;
uint8_t blockCount = 0;

uint32_t freq = 1;
uint32_t duration = 500;

//#########################################################

//once a block has been found, pick it up, then take it to an IR beacon and drop it
//Finally return to last search position so that searching for blocks can continue
void pickUpAndDropOff(uint8_t direction, uint16_t distance);

//#########################################################

void init(void){
	initTimer0();
	initSensor();
	initMotorTimer();
	initLiftMotor();
	initLED();
	init_piezo();
}

void pickUpAndDropOff(uint8_t direction, uint16_t distance){
	//once a block has been found pick it up
	pickupBlock();
	volatile uint16_t sensorRead = 0;
	//Initialize sensor 1 (sensor which looks for bins)
	sensorRead = analogReadSensor(1); 
	//keep track of how far away from start position the manipulator moves
	uint16_t stepCount = 0;
	//start searching for an IR beacon, therefore choose motor 0(moving motor)
	selectMotor(0);
	//changeSpeed(1);
	uint8_t returnDirection = 0;
	//Read the sensor and move until a bin has been found
	//keeping track of the distance and direction that the manipulator has moved
	while (sensorRead < beaconThreshold){
		sensorRead = analogReadSensor(1);
		//blockCount < 2 ||
		if ((distance < 1500 && direction == 1) || (distance > 500 && direction == 0)){
			motorSearch(0, 50);
			returnDirection = 1;
		}
		else{
			motorSearch(1, 50);
			returnDirection = 0;
		}
		stepCount +=50;
	}
	
	// ## A bin has been found ## 
	sensorRead = 0;
	//changeSpeed(2);
	//once a beacon has been found drop the block
	//first realign manipulator over beacon
	selectMotor(0);
	motorSearch(1, 100);
	selectMotor(1);

	dropBlock();
	//select the drive motor and move back to the last searching location
	selectMotor(0);
	//changeSpeed(1);
	
	// Set up the last searching location
	uint16_t noMissDistance = 100;
	motorSearch(returnDirection, (stepCount - noMissDistance));
	
	//Lower the end effector to begin searching for blocks again
	selectMotor(1);
	//drop back down to search height
	uint16_t searchHeight = 260;
	motorSearch(1, searchHeight);
	
	//get ready to start searching left/right again
	//changeSpeed(2);
	selectMotor(0);
	motorSearch(1, 50);
	blockCount ++;
}




int main(void){
	
	//Initialize all main and helper functions
	init();
	
	//Select the motor in the manipulator and start moving along the rail
	selectMotor(0);
	
	//Initialize main variables
	volatile uint16_t sensorRead = 0;
	//Start searching from left to right, assuming that the tallest bin is at the left end
	uint8_t direction = 1;
	uint16_t stepCount = 0;
		
	while(1){
		// ## Start searching for blocks ##
		
		//Read sensor 2 (sensor which looks for blocks)
		sensorRead = analogReadSensor(2);
		
		//Set a threshold value for finding blocks (value tested previously)
		uint16_t blockThreshold = analogReadSensor(2) + 350;
		
		//Start looking for blocks
		while (sensorRead < blockThreshold){
			//Check if the end effector is going to collide with a bin and change direction
			if (stepCount > beamLength){
				//lift the end effector (before it reaches a bin)
				selectMotor(1);
				motorSearch(0, 260);
				//Look for a bin
				volatile uint16_t beaconRead = analogReadSensor(1);
				while (beaconRead < beaconThreshold){
					selectMotor(0);
					motorSearch(direction, 10);
					beaconRead = analogReadSensor(1);
				}
				if (direction == 1){
					motorSearch(1, 100);
				}
				//Change direction
				direction ^= 1;
				stepCount = 0;
				//Realigned the end effector 
				if (direction == 1){
					motorSearch(direction, 75);
				}
				//move away from the bin
				motorSearch(direction, 100);
				//Set the end effector back to its searching height 
				selectMotor(1);
				motorSearch(1, 260);
				selectMotor(0);
 			}
			//Toggle the IR LEDs until a block has been found
			toggleLED(1);
			motorSearch(direction, 1); //Take one step
			stepCount += 1; //Increment the number of steps
			sensorRead = analogReadSensor(2); //read sensor 2 (looking for blocks)
		}
		
		//## A block has been found ##
		//buzz(freq, duration);
		pickUpAndDropOff(direction, stepCount);
		stepCount += 50;
		//Clear the sensor reading and start looking for a new block
		sensorRead = 0;
	}
}



/*
	uint16_t stepCount = 0;
	volatile uint16_t middleSensorRead = analogReadSensor(1);
	while(1){
		while (middleSensorRead < 500){
			changeSpeed(2);
			moveClockwise();
			stepCount++;
			toggleLED(1);
			middleSensorRead = analogReadSensor(1);
		}
		if (middleSensorRead > 500){
			toggleLED(0);
			buzz(freq, duration);
			changeSpeed(1);
			pickupBlock();
			selectMotor(0);
			motorSearch(1, 100);
			middleSensorRead = analogReadSensor(1);
			while(middleSensorRead < 700){
				moveCounterclockwise();
				middleSensorRead = analogReadSensor(1);
			}
		}
		dropBlock();
		stepCount = 500;
		if (stepCount < 0){
			stepCount = 0;
		}
		motorSearch(0, stepCount);
		stepCount = 0;
		middleSensorRead = 0;
	}
*/