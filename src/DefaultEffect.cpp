#include "DefaultEffect.h"
#include "InputEffect.h"
#include "lib/color.h"
#include "lib/effect_runner.h"
#include "lib/noise.h"

DefaultEffect::DefaultEffect() :
	mCycle (0)
{}

void DefaultEffect::beginFrame(const FrameInfo& frame)
{
	const float speed = 1.0;
	mCycle = fmodf(mCycle + frame.timeDelta * speed, 2 * M_PI);
}

void DefaultEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	float distance = len(pixel.point);
	float perlin3 = noise3(pixel.point);
	float wave1 = sinf(0.5 * distance - mCycle) + perlin3;
	float wave2 = sinf(3.0 * distance - mCycle) - perlin3;
	float wave3 = sinf(mCycle);
	hsv2rgb(rgb, wave1, wave3, wave2);
}

