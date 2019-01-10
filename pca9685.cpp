/***** pca9685.cpp *****/

#include "pca9685.h"
#include "Bela.h"
#include <errno.h>

// https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
// https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library/blob/master/Adafruit_PWMServoDriver.cpp
// https://github.com/BelaPlatform/Bela/blob/master/include/I2c.h
// https://forum.bela.io/d/422-reading-gy-521-in-pure-data/8
// https://forum.bela.io/d/442-i2c-accelerometer-class/8
// https://github.com/BelaPlatform/Bela/blob/better-i2c/core/default_libpd_render.cpp
// https://github.com/BelaPlatform/Bela/tree/better-i2c/include
// https://forum.bela.io/d/476-i2c-troubles/3

// write returning -1 is maybe EINTR????
// http://pubs.opengroup.org/onlinepubs/009604499/functions/write.html




// ================================
PCA9685::PCA9685() {}

PCA9685::~PCA9685() {}


// ================================
bool PCA9685::begin(uint8_t address, uint8_t bus)
{
	this->address = address;

	// This functions returns 1 or 2
	if(initI2C_RW(bus, address, 0) > 0)
	{
		int err = errno;
		rt_printf("Something happened while initializing the I2c connection. \tError code %i\n", err);
		return false;
	}

	usleep(10000);

	// Set MODE1 to listen to all calls (bit 0)
	writeRegister(0, 0x80);

	// Set all PWM to output a constant high voltage essentialy turning OFF all LED's
	writeRegister(250, 0 & 0xFF);		// on time byte 1
	writeRegister(251, 0 >> 8);			// on time byte 2
	writeRegister(252, 4095 & 0xFF);	// off time byte 1
	writeRegister(253, 4095 >> 8);		// off time byte 2

	return true;
}


// ================================
void PCA9685::setPWM(unsigned channel, unsigned value)
{
	writeRegister(6 + (4 * channel), value & 0xFF);	// on
	writeRegister(7 + (4 * channel), value >> 8);
	writeRegister(8 + (4 * channel), 4095 & 0xFF);	// off
	writeRegister(9 + (4 * channel), 4095 >> 8);
}


// ================================
void PCA9685::setRGB(unsigned led, unsigned r, unsigned g, unsigned b)
{
	setPWM(led * 3, b);
	setPWM(led * 3 + 1, g);
	setPWM(led * 3 + 2, r);
}

// ================================
void PCA9685::writeRegister(uint8_t reg, uint8_t value)
{
	uint8_t buf[2] = {reg, value};

	if(write(i2C_file, buf, 2) != 2)
	{
		int err = errno;
		rt_printf("Failed to write! Register %i\tAdress %i\tError %i\n", static_cast<int>(reg), address, err);
		return;
	}
}