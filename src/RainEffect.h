#pragma once
#include "JellyEffect.h"

/**
 * TODO: Effect description */
class RainEffect : public JellyEffect
{
public:
	static JellyEffect* Create();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	RainEffect();

	// FIELDS
	uint32_t mOffset;
	float    mHue;
	uint32_t mSpeed;
	uint32_t mMod;
	uint32_t mLen;
};
