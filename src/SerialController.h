#pragma once
#include "BaseController.h"

class SerialController: public BaseController
{
public:
	SerialController(const string& serialDevicePath);
	virtual void Update(uint32_t seconds, bool verbose);

private:
	int       mFileDescriptor;
	uint32_t  mLastCommandTime;
};
