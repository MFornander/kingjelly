#include "ColorHalosEffect.h"
#include "lib/noise.h"

ColorHalosEffect::ColorHalosEffect() :
	mPerlinOctaves(1),
	mPosition{0}
{
}

BaseEffect* ColorHalosEffect::Create()
{
	return new ColorHalosEffect();
}

void ColorHalosEffect::beginFrame(const FrameInfo& frame)
{
	if (InputClicked(3))
		mPerlinOctaves = min(5, mPerlinOctaves+1);
	if (InputClicked(4))
		mPerlinOctaves = max(0, mPerlinOctaves-1);

	for (int index = 0; index < 3; ++index)
		mPosition[index] += frame.timeDelta * (Input(index) - 0.5f);
}

void ColorHalosEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	for (int index = 0; index < 3; ++index)
	{
		Vec3 perlinPoint(pixel.point);
		perlinPoint[1] += mPosition[index];
		rgb[index] = fbm_noise3(perlinPoint, mPerlinOctaves);
	}
}
