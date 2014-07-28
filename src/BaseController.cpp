#include "BaseController.h"


BaseController::BaseController() :
	mDigital(kControlCount),
	mAnalog(kControlCount),
	mEnabled(false)
{}

BaseController::~BaseController()
{}

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

	if (channel >= 'a' && channel <= 'z')
		mAnalog.at(channel - 'a') = max(0.0f, min(1.0f, static_cast<float>(value) / 100.0f));

	if (channel >= 'A' && channel <= 'Z')
		mDigital.at(channel - 'A') = (value != 0);

	if (channel == ':')
		mEnabled = value != 0;
}

