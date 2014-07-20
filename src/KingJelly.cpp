#include "KingJelly.h"
#include "lib/effect_runner.h"
#include "NetworkController.h"
#include "KeyboardController.h"
#include "AdcController.h"
#include "AutoController.h"
#include "EffectManager.h"
#include "JellyEffect.h"


// Detect releasing button 0
// TODO: Refactor to cleaner input->event system?
bool ReleaseButton(const BaseController& controller, uint32_t buttonIndex)
{
	static bool sLastState[4] = {false,false,false,false};
	buttonIndex = min<uint32_t>(buttonIndex, 3);

	bool currentState = controller.Digital(buttonIndex);
	bool clickRelease = sLastState[buttonIndex] && !currentState;

	sLastState[buttonIndex] = currentState;
	return clickRelease;
}

BaseController& GetController()
{
	static AdcController adcController;
	adcController.Update();
	if (adcController.IsEnabled())
		return adcController;

	static KeyboardController keyController;
	keyController.Update();
	if (keyController.IsEnabled())
		return keyController;

	static NetworkController netController;
	netController.Update();
	if (netController.IsEnabled())
		return netController;

	static AutoController autoController;
	autoController.Update();
	return autoController;
}

int main(int argc, char** argv)
{
	// System components
	EffectManager manager;
	EffectRunner runner;

    // Defaults, overridable with command line options
	runner.setMaxFrameRate(300);
	runner.setLayout("scripts/jelly16x100.json");
	if (!runner.parseArguments(argc, argv))
		return 1;

	while (true)
	{
		// Select controller based on 'enabled' reading
		BaseController& controller = GetController();

		// Switch to next or previous effect?
		if (ReleaseButton(controller, 0))
			manager.NextEffect(false);
		if (ReleaseButton(controller, 1))
			manager.NextEffect(true);

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
