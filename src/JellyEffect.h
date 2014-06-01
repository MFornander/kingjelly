#pragma once
#include "KingJelly.h"
#include "lib/effect.h"
#include "lib/color.h"

/**
 * Base class for all KingJelly effects.
 * Please look at DefaultEffect for a full example. */
class JellyEffect: public Effect
{
public:
	static const uint32_t kInputCount = 4;

	// Input setter used by main loop to transfer controller data
	// TODO: refactor with less hardcoded counts
	void  SetInput(uint32_t index, float value);

	// Input getter used by the effect's
	float Input(uint32_t index) const;

protected:
	JellyEffect();
	vector<float> mCurrentInputs;
};

/**
 * Efficient access to jelly strand+led with a single ldiv float operation. */
class JellyPixel
{
public:
	static const uint32_t kStrandCount = 16;  // Strands on Jelly
	static const uint32_t kLedCount = 100;    // LEDs per strand

	JellyPixel(const Effect::PixelInfo& pixelInfo);

	uint32_t Strand() const { return mJellyInfo.quot; }
	uint32_t Led() const    { return mJellyInfo.rem; }

private:
	const ldiv_t mJellyInfo;
};
