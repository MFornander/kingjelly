
/*---------------------------------------------------------
 *   Includes
 *--------------------------------------------------------*/
#include "KingJelly.h"
#include "RainEffect.h"

/*---------------------------------------------------------
 *   Macros
 *--------------------------------------------------------*/
#define ABS(x) ((x<=0)?-x:x)

/*---------------------------------------------------------
 *   Utility Functions
 *--------------------------------------------------------*/
uint32_t mod(int32_t a, int32_t b)
{ 
	return (a%b+b)%b; 
}

/*---------------------------------------------------------
 *   Methods
 *--------------------------------------------------------*/
JellyEffect* RainEffect::Create()
{
	return new RainEffect();
}

RainEffect::RainEffect() :
	mOffset(0),
	mHue(0.5f),
	mSpeed(10),
	mMod(100),
	mLen(10)
{}

void RainEffect::beginFrame(const FrameInfo& frame)
{
	mMod   = 90 + (int)(Input(0)*255.0);
	mHue   = Input(1);
 	mSpeed = (int) ((1.0 - Input(2)) * 20) + 1;
 	mLen   = (int) (Input(3)*50) + 1;
	mOffset++;
}

void RainEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	// position within a given strand
	uint32_t pos = pixel.index % mMod;
	uint32_t off = (mOffset/(int)mSpeed) % JellyPixel::kLedCount;

	// distance from the center pixel of the wave
    int distance = ABS(min(mod(pos - off, JellyPixel::kLedCount),
	        	           mod(off - pos, JellyPixel::kLedCount)));

    // get dimmer based on distance from center
	float wave = max(0.0, (mLen-distance)/	(double)mLen);

	/*
	if(pixel.index > 80 && pixel.index < 100)
		 if(wave != 0.0)
    		printf("%d %d %d (%d = %d, %d = %d) %d %f\n", 
    		       mOffset, pos, off, (pos - off),  mod(pos - off,100), 
    		       off - pos, mod(off - pos, 100), distance,wave);
    */

	hsv2rgb(rgb, mHue, 1.0f, wave);
}
