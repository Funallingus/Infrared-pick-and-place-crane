/*
 * LED control.h
 *
 * Created: 2/10/2015 12:12:43 PM
 *  Author: Lachlan
 */ 


#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include <stdint.h>

void initLED(void);

void toggleLED(uint8_t toggle);

uint8_t LEDPowerCheck(void);



#endif /* LED_CONTROL_H_ */