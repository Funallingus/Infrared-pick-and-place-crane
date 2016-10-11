/*
 * sensor.h
 *
 * Created: 30/09/2015 8:36:14 AM
 *  Author: Lachlan
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

//set up registers to begin adc for IR sensor pins
void initSensor(void);


//digital (high/low) read a pin
uint8_t digitalReadSensor(void);


//read an analog pin
uint16_t analogReadSensor(uint8_t sensor);



#endif /* SENSOR_H_ */