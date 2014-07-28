#include "SerialController.h"
#include <fcntl.h>
#include <unistd.h>

SerialController::SerialController(const string& serialDevicePath) :
	mFileDescriptor(open(serialDevicePath.c_str(), O_RDONLY | O_NOCTTY | O_NDELAY))
{
	 if (mFileDescriptor < 0)
		 fprintf(stderr, "SerialController init error: %d\n", mFileDescriptor);
}

/// Refresh all inputs by processing any pending serial lines
void SerialController::Update()
{
	 if (mFileDescriptor < 0)
		 return;

	char command[256] = {0};
	ssize_t readCount = read(mFileDescriptor, command, 255);

	if (readCount <= 0)
	{
		// TODO: Disable if no data was received in 5 seconds
	}
	else
	{
		fprintf(stdout, "SerialController input: %s\n", command);
		ExecuteCommand(command);
		mEnabled = true;
	}
}
