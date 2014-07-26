#include "AdcReader.h"

AdcReader::AdcReader(adc_name name, uint32_t slotCount, uint32_t samplesRequired) :
	mSlotCount(slotCount),
	mSamplesRequired(samplesRequired),
	mCurrentSlot(0),
	mNewSlot(0),
	mNewCount(0),
	mAIN(name)
{ }

float AdcReader::GetValue()
{
	// Jelly controller potentiometers are hooked up such that
	// ~1790 is leftmost and ~15 is rightmost
	uint32_t value = mAIN.getNumericValue();

	// Clamp values at edges
	if (value > 1750)
		value = 1800;
	if (value < 50)
		value = 0;

	uint32_t slot = mSlotCount * value / 1800;
	if (slot == mNewSlot)
	{
		++mNewCount;
		if (mNewCount >= mSamplesRequired)
			mCurrentSlot = mNewSlot;
	}
	else
	{
		mNewSlot = slot;
		mNewCount = 0;
	}

	return 1.0f - static_cast<float>(mCurrentSlot) / mSlotCount;
}
