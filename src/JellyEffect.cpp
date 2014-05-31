#include "JellyEffect.h"


JellyEffect::JellyEffect() :
	mCurrentInputs(kInputCount)
{}

void JellyEffect::SetInput(uint32_t index, float value)
{
	if (index < kInputCount)
		mCurrentInputs.at(index) = value;
}

float JellyEffect::Input(uint32_t index) const
{
	if (index < kInputCount)
		return mCurrentInputs.at(index);
	return 0;
}


JellyPixel::JellyPixel(const Effect::PixelInfo& pixelInfo) :
	mJellyInfo(ldiv(pixelInfo.index, kStrandCount))
{}
