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
		fprintf(stdout, "SerialController: Open Error=%d\n", mFileDescriptor);

}

/// Refresh all inputs by processing any pending serial lines
void SerialController::Update(uint32_t seconds, bool verbose)
{
	char command[256];
	ssize_t readCount = read(mFileDescriptor, command, 255);
	if (readCount <= 0)
	{
// Only require 5 sec pings in Release
#ifndef DEBUG
		// Disable if no data was received in 10 seconds
		const uint32_t kSecondsUntilDisable = 10;
		if ((seconds - mLastCommandTime) >= kSecondsUntilDisable && mEnabled)
		{
			mEnabled = false;
			fprintf(stdout, "SerialController: Disable after %d secs\n", kSecondsUntilDisable);
		}
#endif
	}
	else
	{
		command[readCount] = 0;
		if (verbose)
			fprintf(stdout, "SerialController: Command = %s", command);
		ExecuteCommand(command);
		mLastCommandTime = seconds;
	}
}

void SerialController::ExecuteCommand(const string& command)
{
	char channel;
	int value;
	if (sscanf(command.c_str(), "%c%d", &channel, &value) != 2)
		return;

	// Lowercase commands are analog inputs
	if (channel >= 'a' && channel <= 'd')
		mAnalog[channel - 'a'] = max(0.0f, min(1.0f, static_cast<float>(value) / 100.0f));

	// Uppercase commands are digital inputs
	else if (channel >= 'A' && channel <= 'D')
		mDigital[channel - 'A'] = (value != 0);

	// Command ':' is the "enable" digital input
	else if (channel == ':')
		mEnabled = value != 0;

	// Report strange commands to debug easier
	else
		fprintf(stderr, "BaseController illegal command: '%s'\n", command.c_str());
}

