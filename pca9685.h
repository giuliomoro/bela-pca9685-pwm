/***** pca9685.h *****/

#pragma once

#include "I2c.h"
#include <cstdint>

class PCA9685 : public I2c
{
public:
	PCA9685();
	~PCA9685();
	
	// Initialize the I2c connection
	bool begin(uint8_t address = 0x40, uint8_t bus = 1);
	
	// Write a single byte directly to memory
	void writeRegister(uint8_t reg, uint8_t value);
	
	// Set a PWM value for specified channel
	// For speed, the value is not clipped inside range
	void setPWM(unsigned channel, unsigned value);
	
	// Set RGB value of a LED
	void setRGB(unsigned led, unsigned r, unsigned g, unsigned b);
	
	// Unused function which has to be implemented by I2c.h
	int readI2C() { return 0; }
	
private:
	int address;	
};