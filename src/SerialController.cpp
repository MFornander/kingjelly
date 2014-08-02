#include "SerialController.h"
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

SerialController::SerialController(const string& serialDevicePath) :
	BaseController("Serial"),
	mFileDescriptor(open(serialDevicePath.c_str(), O_RDONLY | O_NOCTTY | O_NDELAY)),
	mLastCommandSecond(0)
{}

/// Refresh all inputs by processing any pending serial lines
void SerialController::Update()
{
	 if (mFileDescriptor < 0)
		 return;

	char command[256];
	ssize_t readCount = read(mFileDescriptor, command, 255);
	timeval now;
	gettimeofday(&now, 0);

	if (readCount <= 0)
	{
		// Disable if no data was received in 5 seconds
		const time_t kSecondsUntilDisable = 5;
		if ((now.tv_sec - mLastCommandSecond) >= kSecondsUntilDisable)
			mEnabled = false;
	}
	else
	{
		command[255] = 0;
		fprintf(stdout, "SerialController command: %s", command);
		ExecuteCommand(command);
		mEnabled = true;
		mLastCommandSecond = now.tv_sec;
	}
}
