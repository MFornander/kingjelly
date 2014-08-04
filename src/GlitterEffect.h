#pragma once
#include "BaseEffect.h"

class GlitterEffect: public BaseEffect
{
public:
	static BaseEffect* Create();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	GlitterEffect();

	uint32_t mChance;
	float mCycle;
	float mBrightness;
};
