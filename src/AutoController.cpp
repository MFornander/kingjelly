#include "AutoController.h"
#include <cstdlib>
#include <ctime>

AutoController::AutoController() :
	BaseController("Auto"),
	mLastSwitchTime(0)
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	mAnalog[0] = 0.5f;
	mAnalog[1] = 0.5f;
	mAnalog[2] = 0.5f;
	mAnalog[3] = 0.5f;

	mDigital[0] = false;
	mDigital[1] = false;
	mDigital[2] = false;
	mDigital[3] = false;
}

void AutoController::Update(uint32_t seconds, bool verbose)
{
	const uint32_t kSecondsBetweenSwitch = 60;

	if ((seconds - mLastSwitchTime) > kSecondsBetweenSwitch)
	{
		mLastSwitchTime = seconds;

		mDigital[0] = true;
		for (int index = 0; index < 4; ++index)
			mAnalog[index] = GetRandomAnalogValue();

		if (verbose)
			fprintf(stdout, "AutoController: Switch to new effect with analog: (%.2f, %.2f, %.2f, %.2f)\n", mAnalog[0], mAnalog[1], mAnalog[2], mAnalog[3]);
	}
	else
	{
		mDigital[0] = false;
	}
}


float AutoController::GetRandomAnalogValue()
{
	return 0.1f + 0.8f * static_cast<float>(std::rand()) / RAND_MAX;
}
