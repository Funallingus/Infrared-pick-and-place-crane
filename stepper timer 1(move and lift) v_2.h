/*
	
	stepper timer 1(move and lift) v_2.h
	Author: Johanna
*/


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include <stdint.h>

void initMotorTimer(void);
void motorStart (void);
void motorStop (void);
void moveClockwise (void);
void moveCounterclockwise (void);
void initLiftMotor(void);
void selectMotor (int motorSelect);
void changeSpeed (int speed);
void motorSearch (uint8_t direction, uint16_t stepsToTake);
void pickupBlock (void);
void dropBlock (void);


#endif /* INCFILE1_H_ */