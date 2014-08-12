#include "AutoController.h"
#include <cstdlib>
#include <ctime>

AutoController::AutoController() :
	BaseController("Auto")
{
	mAnalog[0] = 0.5f;
	mAnalog[1] = 0.5f;
	mAnalog[2] = 0.5f;
	mAnalog[3] = 0.5f;

	mDigital[0] = false;
	mDigital[1] = false;
	mDigital[2] = false;
	mDigital[3] = false;
}

void AutoController::Update(uint32_t /*seconds*/, bool /*verbose*/)
{
	// Disable switching effects for now to stay at the first
	// effect on boot with no controller attached.
	mNextEffectTag = "0000";
	return;
}
