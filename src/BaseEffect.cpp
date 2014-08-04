#include "BaseEffect.h"


BaseEffect::BaseEffect() :
	mCurrentInputs(kInputCount),
	mLastDown(kInputCount)
{}

void BaseEffect::SetInput(uint32_t index, float value)
{
	if (index < kInputCount)
		mCurrentInputs.at(index) = value;
}

float BaseEffect::Input(uint32_t index) const
{
	if (index < kInputCount)
		return mCurrentInputs.at(index);
	return 0;
}

bool BaseEffect::InputClicked(uint32_t index)
{
	if (index >= kInputCount)
		return false;

	const bool clicked = mCurrentInputs.at(index) == 0 && mLastDown.at(index);
	mLastDown[index] = mCurrentInputs.at(index) != 0;
	return clicked;
}

void BaseEffect::debug(const DebugInfo& /*info*/)
{
	fprintf(stderr, "Input:[%3u,%3u,%3u,%3u,%3u]",
		static_cast<uint32_t>(100 * mCurrentInputs.at(0)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(1)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(2)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(3)),
		static_cast<uint32_t>(100 * mCurrentInputs.at(4)));
}

