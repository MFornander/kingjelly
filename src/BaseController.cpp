#include "BaseController.h"


BaseController::BaseController(const string& name) :
	mName(name),
	mEnabled(false)
{
	// Reset initial values to 50% for all pots and off for switches
	for (int index = 0; index < kControlCount; ++index)
	{
		mAnalog[index] = 0.5f;
		mDigital[index] = false;
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
