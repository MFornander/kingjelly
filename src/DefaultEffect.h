#pragma once
#include "JellyEffect.h"

/**
 * Effect used when Jelly is turned on.
 *
 * Please use this as a template for new effects to maintain a
 * consistent code style of our effect library.
 * NOTE: You must also add a corresponding line in EffectManager's ctor */
class DefaultEffect : public JellyEffect
{
public:
	static JellyEffect* Create();  // Required factory method for all effects

	virtual void beginFrame(const FrameInfo& frame); // Called once per frame
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const; // Called once per LED

private:
	DefaultEffect(); // Private ctor forcing factory-only contruction

	// FIELDS
	float mCycle;
	float mSaturation;
};
