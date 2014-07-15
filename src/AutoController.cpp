#include "AutoController.h"

AutoController::AutoController()
{}

void AutoController::Update()
{
	mAnalog[0] = 0.5f;
	mAnalog[1] = 0.5f;
	mAnalog[2] = 0.5f;
	mAnalog[3] = 0.5f;

	mDigital[0] = 0;
	mDigital[1] = 0;

	mEnabled = true;
}
