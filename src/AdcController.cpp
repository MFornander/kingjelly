#include "AdcController.h"
#include "math.h"


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

	// quantize the result into bins



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


	mAnalog[0] = DeJitter(mAnalog[0], ClampInput(mAIN4));
	mAnalog[1] = DeJitter(mAnalog[1], ClampInput(mAIN6));
	mAnalog[2] = DeJitter(mAnalog[2], ClampInput(mAIN2));
	mAnalog[3] = DeJitter(mAnalog[3], ClampInput(mAIN0));

	mDigital[0] = ClampInput(mAIN1) > 0.5f;
	mDigital[1] = ClampInput(mAIN3) > 0.5f;

	mEnabled = (mAnalog[0] + mAnalog[1] + mAnalog[2] + mAnalog[3]) < 4.0f;
}

float AdcController::DeJitter(float current, float input)
{

//	printf("%f %f %f %f\n", current, input, fabs(current-input), mHysteresis);

	if(fabs(current-input) > mHysteresis)
	{
		return(input);
	}
	else
	{
		return(current);
	}
}

