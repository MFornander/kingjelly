#pragma once
#include "BaseController.h"

class SerialController: public BaseController
{
public:
	SerialController(const string& serialDevicePath);
	virtual void Update();

private:
	int mFileDescriptor;
	time_t mLastCommandSecond;
};
