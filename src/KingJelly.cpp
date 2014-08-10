#include "KingJelly.h"
#include "NetworkController.h"
#include "SerialController.h"
#include "AutoController.h"
#include "EffectManager.h"
#include "BaseEffect.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#include "lib/effect_runner.h"
#pragma GCC diagnostic pop

// Detect releasing button
bool ReleaseButton(const BaseController& controller, uint32_t buttonIndex)
{
	static bool sLastState[4] = {0};
	buttonIndex = min<uint32_t>(buttonIndex, 3);

	bool currentState = controller.Digital(buttonIndex);
	bool clickRelease = sLastState[buttonIndex] && !currentState;

	sLastState[buttonIndex] = currentState;
	return clickRelease;
}

// Select which controller should be active
BaseController& GetController(bool verbose)
{
	static SerialController serialController("/dev/ttyO5");
	static NetworkController netController;
	static AutoController autoController;
	static BaseController* lastController = nullptr;

	timeval now;
	gettimeofday(&now, 0);

	BaseController* newController;
	serialController.Update(now.tv_sec, verbose);
	if (serialController.IsEnabled())
		newController = &serialController;
	else
	{
		netController.Update(now.tv_sec, verbose);
		if (netController.IsEnabled())
			newController = &netController;
		else
		{
			autoController.Update(now.tv_sec, verbose);
			newController = &autoController;
		}
	}

	if (lastController != newController)
	{
		lastController = newController;
		if (verbose)
			fprintf(stdout, "Active Controller: %s\n", lastController->GetName().c_str());
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
		if (ReleaseButton(controller, 0)) // left joystick = prev effect
			manager.NextEffect(false);
		if (ReleaseButton(controller, 1)) // right joystick = next effect
			manager.NextEffect(true);

		BaseEffect& activeEffect = manager.GetActiveInstance();

		// Transfer analog 1,2,3 to effect, 0 is speed
		activeEffect.SetInput(BaseEffect::Pot0, controller.Analog(0));
		activeEffect.SetInput(BaseEffect::Pot1, controller.Analog(1));
		activeEffect.SetInput(BaseEffect::Pot2, controller.Analog(2));
		activeEffect.SetInput(BaseEffect::Pot3, controller.Analog(3));

		// Transfer digital 2,3 to effect, 0,1 are reserved for prev/next effect
		activeEffect.SetInput(BaseEffect::JoyUp, controller.Digital(2));
		activeEffect.SetInput(BaseEffect::JoyDown, controller.Digital(3));

		// Change speed based on analog 0, clamp close to middle values to 0.5
		float speed = controller.Analog(0);
		if (speed >= 0.45f && speed <= 0.55f)
			speed = 0.5f;
		runner.setSpeed(speed * 2.0f);

		// Draw effect frame
		runner.setEffect(&activeEffect);
		runner.doFrame();
	}

	return 0;
}

// Needed for SVL error checking
Void _Assert(Int condition, const Char* errorMessage, const Char* file, Int line)
{
	std::cerr << LVAL(condition) << std::endl;
	__assert(errorMessage, file, line);
}
