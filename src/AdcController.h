#pragma once
#include "BaseController.h"
#include "BlackLib.h"

/**
 * TODO */
class AdcController: public BaseController
{
public:
	AdcController();
	virtual void Update();

private:
	BlackADC mAIN0;
	BlackADC mAIN1;
	BlackADC mAIN2;
	BlackADC mAIN3;
	BlackADC mAIN4;
//	BlackADC mAIN5;  // AIN5 is not connected on the King Jelly 2014 cape
	BlackADC mAIN6;

	static float DeJitter(float current, float input);

	// Bin count to quantize input over
	constexpr static float kBinCount = 32.0f;
	constexpr static float kHysteresis = 1.0f / kBinCount;
};
