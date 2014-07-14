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
