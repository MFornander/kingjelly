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

/// IN PROGRESS
EFFECT(Glitter)
	uint32_t mChance;
	float    mCycle;
	float    mBrightness;
};

/// Overlay of 2D sine patterns
EFFECT(Water)
	float   mTime;
	int32_t mIterations;
	float   mSize;
	float   mGain;
	float   mHue;
};

/// IN PROGRESS
/// HSV rings bouncing with bounded controllable hue range
EFFECT(Bounce)
	float   mTime;
	float   mSpread;
	float   mHue;
	float   mHueRange;
};

/// IN PROGRESS
///
EFFECT(Swirl)
	float   mTime;
	float   mGrain;
	float   mHue1;
	float   mHue2;
};

EFFECT(SinusSnake)
	float   mTime;
};

EFFECT(Fire)
	float   mTime;
	float   mScale;
	Vec3    mHighLight;
	Vec3    mLowLight;
};

