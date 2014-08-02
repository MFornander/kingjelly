#pragma once
#include "BaseEffect.h"

/**
 * TODO: Effect description */
class RainEffect : public BaseEffect
{
public:
	static BaseEffect* Create();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	RainEffect();

	// FIELDS
	uint32_t mOffset;
	float    mHue;
	uint32_t mSpeed;
	uint32_t mMod;
	int32_t  mLen;
};
