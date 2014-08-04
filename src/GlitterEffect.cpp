#include "GlitterEffect.h"
#include "lib/noise.h"

GlitterEffect::GlitterEffect() :
	mChance(0.5f),
	mCycle(0),
	mBrightness(0)
{}

BaseEffect* GlitterEffect::Create()
{
	return new GlitterEffect();
}

void GlitterEffect::beginFrame(const FrameInfo& frame)
{
	mChance = Input(0) * RAND_MAX;
	mCycle += frame.timeDelta;
	mBrightness = 2.0f * Input(1) + sin(mCycle) / 2.0f;
}

void GlitterEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	float value = static_cast<uint32_t>(rand()) <= mChance ? mBrightness : 0;
	Vec3 perlinPoint(pixel.point);
	perlinPoint[1] += mCycle;
	rgb.MakeBlock(value * fbm_noise3(perlinPoint, 3));
}
