#pragma once
#include "BaseController.h"
#include "AdcReader.h"

/**
 * TODO */
class AdcController: public BaseController
{
public:
	AdcController();
	virtual void Update();

private:
	AdcReader mAIN0;
	AdcReader mAIN1;
	AdcReader mAIN2;
	AdcReader mAIN3;
	AdcReader mAIN4;
	AdcReader mAIN5;  // (TODO attach on/off switch here)
	AdcReader mAIN6;
};
