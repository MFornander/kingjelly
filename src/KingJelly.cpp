#include "KingJelly.h"
#include "lib/effect_runner.h"
#include "NetworkController.h"
#include "KeyboardController.h"
#include "GpioController.h"
#include "EffectManager.h"
#include "JellyEffect.h"


// Detect releasing button 0
// TODO: Refactor to cleaner input->event system?
bool ReleaseButton0(const IController& controller)
{
	static bool sLastState = false;
	bool currentState = controller.Digital(0);

	bool clickRelease = sLastState && !currentState;
	sLastState = currentState;
	return clickRelease;
}

int main(int argc, char** argv)
{
	// System components
	EffectManager manager;
	EffectRunner runner;
//	KeyboardController controller;
	GpioController controller;

    // Defaults, overridable with command line options
	runner.setMaxFrameRate(300);
	runner.setLayout("scripts/jelly16x100.json");
	if (!runner.parseArguments(argc, argv))
		return 1;

	while (true)
	{
		// Switch to next effect?
		if (ReleaseButton0(controller))
			manager.NextEffect();

		JellyEffect& activeEffect = manager.GetActiveInstance();

		// Transfer analog control inputs to effect
		controller.Update();
		const uint32_t kInputCount = 4;
		for (uint32_t inputIndex = 0; inputIndex < kInputCount; ++inputIndex)
			activeEffect.SetInput(inputIndex, controller.Analog(inputIndex));

		// Draw effect frame
		runner.setEffect(&activeEffect);
		runner.doFrame();
	}

    return 0;
}
