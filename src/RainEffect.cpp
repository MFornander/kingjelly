#include "KingJelly.h"
#include "RainEffect.h"

#define ABS(x) ((x<0)?-x:x)
JellyEffect* RainEffect::Create()
{
	return new RainEffect();
}

RainEffect::RainEffect() :
	mOffset(0),
	mNoise(1.5f),
	mHue(0.5f)
{}

void RainEffect::beginFrame(const FrameInfo& frame)
{
	mNoise = 1.0f + Input(0);
	mHue   = Input(1);

	// advance down the strand 
	mOffset++;
}

void RainEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	// position within a given strand
	int pos = pixel.index % static_cast<int>(JellyPixel::kLedCount * mNoise);

	// distance from the center pixel of the wave
    int distance = ABS(min((pos - mOffset/10) % JellyPixel::kLedCount,
	        	                 (mOffset/10 - pos) % JellyPixel::kLedCount));

    // get dimmer based on distance from center
	float wave = max(0.0, (10-distance)/10.0);

	hsv2rgb(rgb, mHue, 1.0f, wave);
}
