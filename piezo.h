/*
 * IncFile1.h
 *
 * Created: 15/10/2015 11:41:19 AM
 *  Author: s4356281
 */ 


#ifndef PIEZO_H_
#define PIEZO_H_

//set up registers
void init_piezo(void);


//buzz
void buzz(uint32_t freq, uint32_t duration);


#endif /* PIEZO_H_ */