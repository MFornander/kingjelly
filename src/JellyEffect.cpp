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

void JellyEffect::debug(const DebugInfo& info)
{
	fprintf(stderr, "Controls: [%3u,%3u,%3u,%3u,%3u] --",
		static_cast<uint32_t>(100 * mCurrentInputs.at(0)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(1)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(2)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(3)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(4)));
}

JellyPixel::JellyPixel(const Effect::PixelInfo& pixelInfo) :
	mJellyInfo(ldiv(pixelInfo.index, kStrandCount))
{}
