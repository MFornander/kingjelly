#include "EffectMattias.h"
#include "lib/noise.h"
#include "lib/color.h"

// --- PerlinRainbow ---
PerlinRainbow::PerlinRainbow() :
	mCycle(0),
	mSaturation(0),
	mVerticalOffset(0)
{}

void PerlinRainbow::beginFrame(const FrameInfo& frame)
{
	const float speed2 = Input(Pot1);
	mSaturation = Input(Pot2);
	mCycle = fmodf(mCycle + frame.timeDelta * speed2, 2 * M_PI);
	mVerticalOffset += Input(Pot3) * 2.0f * frame.timeDelta;
}

void PerlinRainbow::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	Vec3 point = pixel.point;
	point[1] += mVerticalOffset;

	float distance = len(pixel.point);
	float perlin3 = noise3(point);
	float wave1 = sinf(0.5 * distance - mCycle) + perlin3;
	float wave2 = sinf(3.0 * distance - mCycle) - perlin3;
	float wave3 = sinf(mCycle);

	hsv2rgb(rgb, wave1, mSaturation * wave3, wave2);
}


// --- ColorFlow ---
ColorFlow::ColorFlow() :
	mPerlinOctaves(1),
	mPosition{0}
{}

void ColorFlow::beginFrame(const FrameInfo& frame)
{
	if (InputClicked(JoyUp))
		mPerlinOctaves = min(5, mPerlinOctaves+1);
	if (InputClicked(JoyDown))
		mPerlinOctaves = max(0, mPerlinOctaves-1);

	for (int index = 0; index < 3; ++index)
		mPosition[index] += frame.timeDelta * (Input(static_cast<EInput>(index)) - 0.5f);
}

void ColorFlow::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	for (int index = 0; index < 3; ++index)
	{
		Vec3 perlinPoint(pixel.point);
		perlinPoint[1] += mPosition[index];
		rgb[index] = fbm_noise3(perlinPoint, mPerlinOctaves);
	}
}

// --- GlitterEffect ---
Glitter::Glitter() :
	mChance(0.5f),
	mCycle(0),
	mBrightness(0)
{}

void Glitter::beginFrame(const FrameInfo& frame)
{
	mChance = Input(Pot1) * RAND_MAX;
	mCycle += frame.timeDelta;
	mBrightness = 2.0f * Input(Pot2) + sin(mCycle) / 2.0f;
}

void Glitter::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	float value = static_cast<uint32_t>(rand()) <= mChance ? mBrightness : 0;
	Vec3 perlinPoint(pixel.point);
	perlinPoint[1] += mCycle;
	rgb.MakeBlock(value * fbm_noise3(perlinPoint, 3));
}
