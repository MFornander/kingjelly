#pragma once
#include "BlackLib.h"

class AdcReader
{
public:
	AdcReader(adc_name name, uint32_t slotCount, uint32_t samplesRequired);
	float GetValue();

private:
	uint32_t mSlotCount;
	uint32_t mSamplesRequired;
	uint32_t mCurrentSlot;
	uint32_t mNewSlot;
	uint32_t mNewCount;
	BlackADC mAIN;
};
