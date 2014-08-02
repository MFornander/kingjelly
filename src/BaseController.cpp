#include "BaseController.h"


BaseController::BaseController(const string& name) :
	mDigital(kControlCount),
	mAnalog(kControlCount),
	mEnabled(false),
	mName(name)
{}

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

bool BaseController::Digital(uint32_t index) const
{
	if (index < mDigital.size())
		return mDigital.at(index);
	return false;
}

float BaseController::Analog(uint32_t index) const
{
	if (index < mAnalog.size())
		return mAnalog.at(index);
	return 0;
}

void BaseController::ExecuteCommand(const string& command)
{
	char channel;
	int value;
	if (sscanf(command.c_str(), "%c%d", &channel, &value) != 2)
		return;

	// Lowercase commands are analog inputs
	if (channel >= 'a' && channel <= 'z')
		mAnalog.at(channel - 'a') = max(0.0f, min(1.0f, static_cast<float>(value) / 100.0f));

	// Uppercase commands are digital inputs
	else if (channel >= 'A' && channel <= 'Z')
		mDigital.at(channel - 'A') = (value != 0);

	// Command ':' is the "enable" digital input
	else if (channel == ':')
		mEnabled = value != 0;

	// Report strange commands to debug easier
	else
		fprintf(stderr, "BaseController illegal command: '%s'\n", command.c_str());
}

