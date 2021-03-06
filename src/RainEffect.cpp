
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

 const vector<uint32_t> RainEffect::mMods_vect = {97,100,103,138};

/*---------------------------------------------------------
 *   Methods
 *--------------------------------------------------------*/
RainEffect::RainEffect() :
	mOffset(0),
	mHue(0.5f),
	mModIdx(0),
	mLen(10)
{}

void RainEffect::beginFrame(const FrameInfo& frame)
{
	if (InputClicked(JoyUp))
		mModIdx++;
	if (InputClicked(JoyDown))
		mModIdx--;
	mModIdx %= mMods_vect.size();

	mHue   = Input(Pot1);
 	mLen   = (int) (Input(Pot2)*50) + 1;
	
	mOffset += (frame.timeDelta*32);
}

void RainEffect::shader(Vec3& rgb, const PixelInfo& pixel) const
{
	// position within a given strand
	uint32_t pos = pixel.index % mMods_vect.at(mModIdx);
	uint32_t off = ((int)mOffset) % JellyPixel::kLedCount;

	// distance from the center pixel of the wave
	int distance = ABS(min(mod(pos - off, JellyPixel::kLedCount),
	        	           mod(off - pos, JellyPixel::kLedCount)));

	// get dimmer based on distance from center
	float wave = max(0.0, (mLen-distance)/(double)mLen);

	/*
	if(pixel.index > 80 && pixel.index < 100)
		 if(wave != 0.0)
    		printf("%d %d %d (%d = %d, %d = %d) %d %f\n", 
    		       mOffset, pos, off, (pos - off),  mod(pos - off,100), 
    		       off - pos, mod(off - pos, 100), distance,wave);
	*/

	if(wave == 0)
	{
		hsv2rgb(rgb, fmodf(mHue+0.1,1.0), 1.0f, Input(Pot3));
	}
	else
	{
		hsv2rgb(rgb, mHue, 1.0f, wave);
	}

	//printf("%d : (%f %f %f) : %f %f %f\n", pixel.index, rgb[0], rgb[1], rgb[2],mHue,1.0,wave);

}
