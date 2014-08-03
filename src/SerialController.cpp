#include "SerialController.h"
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

SerialController::SerialController(const string& serialDevicePath) :
	BaseController("Serial"),
	mFileDescriptor(-1),
	mLastCommandTime(0)
{
	mEnabled = true;
	mFileDescriptor = open(serialDevicePath.c_str(), O_RDONLY | O_NOCTTY | O_NDELAY);
	if (mFileDescriptor < 0)
		fprintf(stderr, "SerialController: Open Error=%d\n", mFileDescriptor);

}

/// Refresh all inputs by processing any pending serial lines
void SerialController::Update(uint32_t seconds, bool verbose)
{
	 if (mFileDescriptor < 0)
		 return;

	char command[256];
	ssize_t readCount = read(mFileDescriptor, command, 255);
	if (readCount <= 0)
	{
#ifdef NDEBUG
		// Disable if no data was received in 5 seconds
		const uint32_t kSecondsUntilDisable = 5;
		if ((seconds - mLastCommandTime) >= kSecondsUntilDisable && mEnabled)
		{
			mEnabled = false;
			fprintf(stdout, "SerialController: Timeout");
		}
#endif
	}
	else
	{
		command[readCount] = 0;
		if (verbose)
			fprintf(stdout, "SerialController: command '%s'", command);
		ExecuteCommand(command);
		mLastCommandTime = seconds;
	}
}
