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

KeyboardController::KeyboardController()
{}

/// Refresh all channels by processing stdin lines since last Update call
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
