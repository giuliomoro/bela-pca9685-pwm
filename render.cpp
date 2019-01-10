/***** render.cpp *****/
#include <Bela.h>
#include <pca9685.h>

PCA9685 pwm1;
PCA9685 pwm2;
PCA9685 pwm3;

void auxFunc(void*)
{
	pwm1.setPWM(15, 0);
	pwm2.setPWM(15, 0);
	pwm3.setPWM(15, 0);
	usleep(1000000);
	pwm1.setPWM(15, 4000);
	pwm2.setPWM(15, 4000);
	pwm3.setPWM(15, 4000);
	usleep(1000000);
	for(unsigned int n = 0; n < 10; ++n)
	{
		if(gShouldStop)
			return;
		pwm1.setPWM(15, 0);
		pwm2.setPWM(15, 4000);
		pwm3.setPWM(15, 4000);
		usleep(300000);
		pwm1.setPWM(15, 4000);
		pwm2.setPWM(15, 0);
		pwm3.setPWM(15, 4000);
		usleep(300000);
		pwm1.setPWM(15, 4000);
		pwm2.setPWM(15, 4000);
		pwm3.setPWM(15, 0);
		usleep(300000);
	}
	pwm1.setPWM(15, 4095);
	pwm2.setPWM(15, 4095);
	pwm3.setPWM(15, 4095);
}

bool setup(BelaContext* context, void* userData) {

	pwm1.begin(0x40);
	pwm2.begin(0x41);
	pwm3.begin(0x42);
	Bela_scheduleAuxiliaryTask(Bela_createAuxiliaryTask(auxFunc, 90, "i2c", NULL));
	return true;
}

void render(BelaContext* context, void* userData) {
}

void cleanup(BelaContext* context, void* userData) {
}