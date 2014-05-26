#include "KingJelly.h"
#include "KeyboardState.h"
#include "EffectManager.h"
#include "lib/effect_runner.h"


int main(int argc, char** argv)
{
	KeyboardState state;
	EffectManager manager;
	EffectRunner runner;

    // Defaults, overridable with command line options
	runner.setMaxFrameRate(300);
	runner.setLayout("scripts/jelly16x100.json");
	if (!runner.parseArguments(argc, argv))
		return 1;

	Effect* currentEffect = nullptr;
	while(true)
	{
		manager.SetState(state);
		Effect* newEffect = manager.GetEffect();
		if (newEffect != currentEffect)
		{
			currentEffect = newEffect;
			runner.setEffect(currentEffect);
		}

		runner.doFrame();
	}

    return 0;
}
