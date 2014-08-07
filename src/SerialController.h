#pragma once
#include "BaseController.h"

class SerialController: public BaseController
{
public:
	SerialController(const string& serialDevicePath);
	virtual void Update(uint32_t seconds, bool verbose);

private:
	/// Execute a single set-input command such as "b42"
	void ExecuteCommand(const string& command);

	// FIELDS
	int       mFileDescriptor;
	uint32_t  mLastCommandTime;
};
