/*
 * Test code.c
 *
 * Created: 5/10/2015 9:02:18 AM
 *  Author: Lachlan
 */ 

/* TEST CODE */

/*
	init();
	selectMotor(0);
	volatile uint16_t sensorRead = 0;

	uint16_t stepCount = 0;
	//changeSpeed(2);
	uint32_t currentTime, lastMoveTime, delayTime, stepTime;
	delayTime = 1000;
	stepTime = 50;
	while(1){
		sensorRead = analogReadSensor(2);
		uint16_t blockThreshold = analogReadSensor(2) + 350;
		while (sensorRead < blockThreshold){
			toggleLED(1);
			motorSearch(1, 1);
			stepCount += 1;
			sensorRead = analogReadSensor(2);
		}
		pickUpAndDropOff(1, stepCount);
		stepCount = 0;
		currentTime = getClockTicks();
		lastMoveTime = currentTime;
		while (currentTime <= lastMoveTime + delayTime){
			currentTime = getClockTicks();
		}
		sensorRead = 0;
	}
*/

/* Working complete block and bin interaction (returns to beacon at fast speed)
	init();
	selectMotor(0);
	volatile uint16_t sensorRead = analogReadSensor(2);
	uint16_t thresholdValue = 350;
	uint16_t stepCount = 0;
	//changeSpeed(2);
	uint32_t currentTime, lastMoveTime, delayTime;
	delayTime = 1000;
	while(1){
		sensorRead = analogReadSensor(2);
		if(sensorRead < thresholdValue){
			toggleLED(1);
			motorSearch(1, 5);
			stepCount += 5;
		}
		else{
			toggleLED(0);
			pickUpAndDropOff(1, stepCount);
			currentTime = getClockTicks();
			lastMoveTime = currentTime;
			while (currentTime <= lastMoveTime + delayTime){
				currentTime = getClockTicks();
			}
			sensorRead = 0;
		}
	}
*/


/*Stop on a block and return to start
	init();
	selectMotor(0);
	volatile uint16_t sensorRead = analogReadSensor(2);
	uint16_t thresholdValue = 350;
	uint16_t stepCount = 0;
	//changeSpeed(2);
	uint32_t currentTime, lastMoveTime, delayTime, stepTime;
	delayTime = 1000;
	stepTime = 50;
	while(1){
		sensorRead = analogReadSensor(2);
		if(sensorRead < thresholdValue){
			toggleLED(1);
			motorSearch(1, 5);
			stepCount += 5;
		}
		else{
			motorSearch(0, stepCount);
			stepCount = 0;
			currentTime = getClockTicks();
			lastMoveTime = currentTime;
			while (currentTime <= lastMoveTime + delayTime){
				currentTime = getClockTicks();
			}
			sensorRead = 0;
		}
	}
*/

/* TEST AUTOMATION
	init();
	selectMotor(0);
	uint16_t stepCount = 0;
	volatile uint16_t middleSensorRead = analogReadSensor(1);
	while(1){
		while (middleSensorRead < 700){
			changeSpeed(2);
			moveClockwise();
			stepCount++;
			toggleLED(1);
			middleSensorRead = analogReadSensor(1);
		}
		if (middleSensorRead > 700){
			toggleLED(0);
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


/* TEst interaction
	init();
	init_serial_stdio(9600, 0);
	//left sensor == sensor 1 (ADC0)
	volatile uint16_t sensorLeftRead = 0;
	
	// middle sensor == sensor 2 (ADC1)
	volatile uint16_t sensorMiddleRead = 0;
	
	//right sensor == sensor 3 (ADC2)
	volatile uint16_t sensorRightRead = 0;
	
	//start with LED's off
	toggleLED(1);
	
	//boolean value for direction of manipulator (1 == clockwise, 0 == antickockwise)
	uint8_t direction = 1;
	
	while(1){
		sensorMiddleRead = analogReadSensor(1);
		printf("Sensor reads:c %d \n", sensorMiddleRead);
	}
*/

/*v TEST beacon interaction code
		sensorRightRead = analogReadSensor(1);
		sensorLeftRead = analogReadSensor(3);
		while ((sensorLeftRead < beaconThreshold) && (sensorRightRead < beaconThreshold)){
			rotate(direction);
		}
		switch (direction){
			case 0:
			moveClockwise(pushOffDistance, 1);
			direction = 1;
			break;
			
			case 1:
			moveCCW(pushOffDistance, 1);
			direction = 0;
			break;
		}
		//reset sensor readings
		sensorLeftRead = 0;
		sensorRightRead = 0;
	}
*/





/* ADC TEST CODE
	initTimer0();
	initSensor();
	init_serial_stdio(9600,0);
	printf("ADC Test\n");
	uint16_t adcConversion = 0;
	uint32_t currentTime, lastConversions, waitTime;
	waitTime = 100;
	currentTime = getClockTicks();
	lastConversions = currentTime;
	while(1) {
		currentTime = getClockTicks();
		if (currentTime <= lastConversions + waitTime){
			adcConversion = analogReadSensor();
			printf("Sensor reads: %4d \n", adcConversion);
			lastConversions = currentTime;
		}
	}
*/


/* LED FLASHING TEST CODE
	initTimer0();
	initLED();
	uint32_t currentTime, lastToggleTime, toggleInterval;
	currentTime = getClockTicks();
	lastToggleTime = currentTime;
	toggleInterval = 1000;
	while(1){
		currentTime = getClockTicks();
		if (currentTime >= lastToggleTime + toggleInterval){
			if (LEDPowerCheck()){
				toggleLED(0);
			}
			else if (!LEDPowerCheck()){
				toggleLED(1);
			}
			lastToggleTime = currentTime;
		}
		else{;}
	}
*/

/* Motor control test code
	initTimer0();
	initMotorControl();
	while(1){
		rotateClockwise(1);
		stepCCW(2);
	}
//////////////////////////////////////////////////////////////////////////
	initTimer0();
	initMotorControl();
	while(1){
		moveClockwise(1000, 1);
		moveCCW(1000, 2);
		moveClockwise(1000, 2);
		moveCCW(1000, 1);
	}
//////////////////////////////////////////////////////////////////////////
	initTimer0();
	initMotorControl();
	while(1){
		rotateClockwise(2);
		stepCCW(1);
	}
*/


/*
	init();
	volatile uint16_t ADCreading = 0;
	uint32_t currentTime = getClockTicks();
	uint32_t lastSensorRead = 0;
	uint32_t sensorReadInterval = 50;
	moveClockwise(lift_distance, 2);
	while(1){
		ADCreading = analogReadSensor(1);
		toggleLED(1);
		while (ADCreading < block_threshold){
			rotateCCW(1);
			currentTime = getClockTicks();
			if (currentTime >= lastSensorRead +	sensorReadInterval){
				ADCreading = analogReadSensor(1);
				lastSensorRead = currentTime;
			}
		}
		if (ADCreading >= block_threshold){
			moveCCW(lift_distance, 2);
			volatile uint32_t pause = getClockTicks();
			while ((getClockTicks() - pause) < wait_time){
				pause = getClockTicks();
			}
			moveClockwise(lift_distance, 2);
			toggleLED(0);
			volatile uint16_t BeaconADCRead = 0;
			while (BeaconADCRead < beacon_threshold){
				BeaconADCRead = analogReadSensor(1);
				stepClockwise(1);
			}
			if (BeaconADCRead >= beacon_threshold){
				moveCCW(push_off_distance, 2);
				moveClockwise(push_off_distance, 2);
				moveCCW(beacon_escape_distance, 1);
			}
		}
	}
*/

/* ADC calibration code
	initTimer0();
	initMotorControl();
	init_serial_stdio(9600, 0);
	initSensor();
	volatile uint16_t steps = 0;
	uint16_t adcReading = 0;
	while (1){
		ADCSRA &= ~(1 << ADEN);
		moveCCW(500, 2);
		ADCSRA |= (1 << ADEN);
		while (steps <= 500){
			stepClockwise(2);
			DDRD = 0xFF;
			adcReading = analogReadSensor(1);
			printf("sensor reading: %d \n", adcReading);
			steps++;
		}
		steps = 0;
	}
*/
