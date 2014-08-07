#pragma once
#include "BaseEffect.h"

/// TODO
EFFECT(PerlinRainbow)
	float mCycle;
	float mSaturation;
	float mVerticalOffset;
};

/**
 * Independently control the motion of Red, Green, and Blue noise
 * with the three pots.  Up and down controls the noise level. */
EFFECT(ColorFlow)
	int32_t mPerlinOctaves;
	float   mPosition[3];
};

/// TODO
EFFECT(Glitter)
	uint32_t mChance;
	float    mCycle;
	float    mBrightness;
};
