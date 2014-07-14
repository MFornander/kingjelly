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
//	BlackADC mAIN5;
	BlackADC mAIN6;
};
