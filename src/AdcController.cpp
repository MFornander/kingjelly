#include "AdcController.h"
#include <cmath>

AdcController::AdcController() :
	mAIN0(AIN0, 10, 5),  // 10 slots, 5 stable readings to change
	mAIN1(AIN1, 2, 1),   // 2 slots, 1 stable reading to change
	mAIN2(AIN2, 10, 5),
	mAIN3(AIN3, 2, 1),
	mAIN4(AIN4, 10, 5),
	mAIN5(AIN5, 2, 1),
	mAIN6(AIN6, 10, 5)
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

