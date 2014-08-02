#include "PerlinRainbow.h"
#include "lib/noise.h"
#include "lib/color.h"


BaseEffect* PerlinRainbow::Create()
{
	return new PerlinRainbow();
}

PerlinRainbow::PerlinRainbow() :
	mCycle(0),
	mSaturation(0)
{}

void PerlinRainbow::beginFrame(const FrameInfo& frame)
{
	const float speed = Input(0) * 4.0f;
	mSaturation = Input(1);
	mCycle = fmodf(mCycle + frame.timeDelta * speed, 2 * M_PI);
}

void PerlinRainbow::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	float distance = len(pixel.point);
	float perlin3 = noise3(pixel.point);
	float wave1 = sinf(0.5 * distance - mCycle) + perlin3;
	float wave2 = sinf(3.0 * distance - mCycle) - perlin3;
	float wave3 = sinf(mCycle);

	hsv2rgb(rgb, wave1, mSaturation * wave3, wave2);
}
