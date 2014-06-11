#include "KeyboardController.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <string>
#include <iostream>

// Ninja snippet from http://cc.byexamples.com/2007/04/08/non-blocking-user-input-in-loop-without-ncurses/
bool IsInputAvailable()
{
	timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	return FD_ISSET(0, &fds);
}

KeyboardController::KeyboardController() :
	mDigital(kControlCount),
	mAnalog(kControlCount)
{}

void KeyboardController::Update()
{
	// Get any lines typed without waiting
	const uint32_t kMaxLength = 10;
	char input[kMaxLength];
	while (IsInputAvailable() && fgets(input, kMaxLength, stdin) != NULL)
	{
		// Strip the trailing newline and execute the line as a command
		string command(input);
		command.resize(command.size() -1);
		ExecuteCommand(command);
	}
}

bool KeyboardController::Digital(uint32_t index) const
{
	if (index < mDigital.size())
		return mDigital.at(index);
	return false;
}

float KeyboardController::Analog(uint32_t index) const
{
	if (index < mAnalog.size())
		return mAnalog.at(index);
	return 0;
}

void KeyboardController::ExecuteCommand(const string& command)
{
	char channel;
	int value;
	if (sscanf(command.c_str(), "%c%d", &channel, &value) != 2)
		return;

	if (channel >= 'a' && channel <= 'z')
		mAnalog.at(channel - 'a') = max(0.0f, min(100.0f, static_cast<float>(value) / 100.0f));

	if (channel >= 'A' && channel <= 'Z')
		mDigital.at(channel - 'A') = (value != 0);
}
