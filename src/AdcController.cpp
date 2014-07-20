#include "AdcController.h"
#include <cmath>

float ClampInput(BlackADC& adc)
{
	// Jelly controller potentiometers are hooked up such that
	// ~1790 is leftmost and ~15 is rightmost
	float value = adc.getNumericValue();

	// Clamp values at edges
	if (value > 1750.0f)
		value = 1800.0f;
	if (value < 50.0f)
		value = 0;

	// Return an inverted value from 0.0 to 1.0 such that
	// leftmost (ccw) is 0, and rightmost (cw) is 1.
	return 1.0f - (value / 1800.0f);
}

AdcController::AdcController() :
	mAIN0(AIN0),
	mAIN1(AIN1),
	mAIN2(AIN2),
	mAIN3(AIN3),
	mAIN4(AIN4),
//	mAIN5(AIN5),
	mAIN6(AIN6)
{}

void AdcController::Update()
{
	// The following map of AIN to analog reflects the King Jelly 2014
	// controller where analog0 is the leftmost potentiomenter and analog3 is
	// the rightmost.
	mAnalog[0] = DeJitter(mAnalog[0], ClampInput(mAIN4));
	mAnalog[1] = DeJitter(mAnalog[1], ClampInput(mAIN6));
	mAnalog[2] = DeJitter(mAnalog[2], ClampInput(mAIN2));
	mAnalog[3] = DeJitter(mAnalog[3], ClampInput(mAIN0));

	// Mapping digital0 to joystick left and digital1 to joystick right.
	// joystick up and down are unmapped this year.
	mDigital[0] = ClampInput(mAIN1) > 0.5f;
	mDigital[1] = ClampInput(mAIN3) > 0.5f;

	// Enabled equals power off such that all analog inputs are off which maps to
	// four 1.0 values.  Note that this can be achieved by turning all potentiometers
	// all the way to the right.  Since we are mapping the first analog to brightness
	// it will turn off the controller if you turn down the brightness to zero and turn
	// the other three controls to the far right.
	mEnabled = (mAnalog[0] + mAnalog[1] + mAnalog[2] + mAnalog[3]) < 4.0f;
}

float AdcController::DeJitter(float current, float input)
{
//	printf("%f %f %f %f\n", current, input, fabs(current-input), mHysteresis);
	if (std::abs(current - input) > kHysteresis)
		return input;
	else
		return current;
}

