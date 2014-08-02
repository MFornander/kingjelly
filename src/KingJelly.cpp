#include "KingJelly.h"
#include "lib/effect_runner.h"
#include "NetworkController.h"
#include "SerialController.h"
#include "AutoController.h"
#include "EffectManager.h"
#include "BaseEffect.h"


// Detect releasing button
bool ReleaseButton(const BaseController& controller, uint32_t buttonIndex)
{
	static bool sLastState[4] = {false,false,false,false};
	buttonIndex = min<uint32_t>(buttonIndex, 3);

	bool currentState = controller.Digital(buttonIndex);
	bool clickRelease = sLastState[buttonIndex] && !currentState;

	sLastState[buttonIndex] = currentState;
	return clickRelease;
}

BaseController& GetController(bool verbose)
{
	static SerialController serialController("/dev/ttyO5");
	static NetworkController netController;
	static AutoController autoController;
	static BaseController* lastController = nullptr;

	BaseController* newController;
	serialController.Update();
	if (serialController.IsEnabled())
		newController = &serialController;
	else
	{
		netController.Update();
		if (netController.IsEnabled())
			newController = &netController;
		else
		{
			autoController.Update();
			newController = &autoController;
		}
	}

	if (lastController != newController)
	{
		lastController = newController;
		fprintf(stdout, "New Controller: %s\n", lastController->GetName().c_str());
	}

	return *newController;
}

int main(int argc, char** argv)
{
	// System components
	EffectManager manager;
	EffectRunner runner;

	// Defaults, overridable with command line options
	runner.setMaxFrameRate(300);
	runner.setLayout("/opt/git/kingjelly/scripts/jelly16x100.json");
	if (!runner.parseArguments(argc, argv))
		return 1;

	while (true)
	{
		// Select controller based on each 'IsEnabled' reading
		BaseController& controller = GetController(runner.isVerbose());

		// Switch to next or previous effect?
		if (ReleaseButton(controller, 0))
			manager.NextEffect(false);
		if (ReleaseButton(controller, 1))
			manager.NextEffect(true);

		BaseEffect& activeEffect = manager.GetActiveInstance();

		// Transfer analog 1,2,3 inputs to effect, 0 is reserved for speed
		activeEffect.SetInput(0, controller.Analog(1));
		activeEffect.SetInput(1, controller.Analog(2));
		activeEffect.SetInput(2, controller.Analog(3));

		// Transfer digital 2,3 inputs to effect, 0,1 are reserved for prev/next effect
		activeEffect.SetInput(3, controller.Digital(2));
		activeEffect.SetInput(4, controller.Digital(3));

		// Change speed based on analog 0, clamp close to middle values to 0.5
		float speed = controller.Analog(0);
		if (speed > 0.4f && speed < 0.6f)
			speed = 0.5f;
		runner.setSpeed(speed * 2.0f);

		// Draw effect frame
		runner.setEffect(&activeEffect);
		runner.doFrame();
	}

    return 0;
}
