#pragma once
#include "BaseEffect.h"

/// TODO
EFFECT(M001, PerlinRainbow)
	float mCycle;
	float mSaturation;
	float mVerticalOffset;
};

/**
 * Independently control the motion of Red, Green, and Blue noise
 * with the three pots.  Up and down controls the noise level. */
EFFECT(M002, ColorFlow)
	int32_t mPerlinOctaves;
	float   mPosition[3];
};

/// IN PROGRESS
EFFECT(M003, Glitter)
	uint32_t mChance;
	float    mCycle;
	float    mBrightness;
};

/// Overlay of 2D sine patterns
EFFECT(M004, Water)
	float   mTime;
	int32_t mIterations;
	float   mSize;
	float   mGain;
	float   mHue;
};

EFFECT(M005, Swirl)
	float   mTime;
	float   mGrain;
	float   mHue1;
	float   mHue2;
};

EFFECT(M006, SinusSnake)
	float   mTime;
};

EFFECT(M007, Fire)
	float   mTime;
	float   mScale;
	Vec3    mHighLight;
	Vec3    mLowLight;
};

EFFECT(M008, Particles)
	float    mTime;
	int32_t  mCount;
	float    mSize;
	float    mHueRange;
	float    mHueStart;

	static const int32_t kMaxCount = 7;
};

EFFECT(M009, Beacon)
	float  mTime;
	float  mSize;
	float  mBand;
};

