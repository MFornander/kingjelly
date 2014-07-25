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
	mAIN0(AIN0, 11, 20), // 11 slots, 20 readings to change
	mAIN1(AIN1, 2, 1),   // 2 slots, 1 reading to change
	mAIN2(AIN2, 11, 20),
	mAIN3(AIN3, 2, 1),
	mAIN4(AIN4, 11, 20),
	mAIN5(AIN5, 2, 1),
	mAIN6(AIN6, 11, 20)
{}

void AdcController::Update()
{
	// The following map of AIN to analog reflects the King Jelly 2014
	// controller where analog0 is the leftmost potentiomenter and analog3 is
	// the rightmost.
	mAnalog[0] = mAIN4.GetValue();
	mAnalog[1] = mAIN6.GetValue();
	mAnalog[2] = mAIN2.GetValue();
	mAnalog[3] = mAIN0.GetValue();

	// Mapping digital-0 to joystick left and digital-1 to joystick right.
	// joystick up and down are unmapped this year.
	// TODO: We will connect digital-2 to the main switch.
	mDigital[0] = mAIN1.GetValue() > 0.5f;
	mDigital[1] = mAIN3.GetValue() > 0.5f;
	mDigital[2] = mAIN5.GetValue() > 0.5f;

	// Enabled equals power off such that all analog inputs are off which maps to
	// four 1.0 values.  Note that this can be achieved by turning all potentiometers
	// all the way to the right.  Since we are mapping the first analog to brightness
	// it will turn off the controller if you turn down the brightness to zero and turn
	// the other three controls to the far right.
	mEnabled = (mAnalog[0] + mAnalog[1] + mAnalog[2] + mAnalog[3]) < 4.0f;
}

