#include "BaseController.h"


BaseController::BaseController(const string& name) :
	mName(name),
	mEnabled(false)
{
	// Reset initial values to 50% for all pots
	for (int index = 0; index < kControlCount; ++index)
	{
		mDigital[index] = false;
		mAnalog[index] = 0.5f;
	}
}

BaseController::~BaseController()
{}

const string& BaseController::GetName() const
{
	return mName;
}

bool BaseController::IsEnabled() const
{
	return mEnabled;
}

void BaseController::ExecuteCommand(const string& command)
{
	char channel;
	int value;
	if (sscanf(command.c_str(), "%c%d", &channel, &value) != 2)
		return;

	// Lowercase commands are analog inputs
	if (channel >= 'a' && channel < 'a' + kControlCount)
		mAnalog[channel - 'a'] = max(0.0f, min(1.0f, static_cast<float>(value) / 100.0f));

	// Uppercase commands are digital inputs
	else if (channel >= 'A' && channel < 'A' + kControlCount)
		mDigital[channel - 'A'] = (value != 0);

	// Command ':' is the "enable" digital input
	else if (channel == ':')
		mEnabled = value != 0;

	// Report strange commands to debug easier
	else
		fprintf(stdout, "BaseController illegal command: '%s'\n", command.c_str());
}

