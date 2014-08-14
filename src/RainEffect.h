#pragma once
#include "BaseEffect.h"

EFFECT(B001, RainEffect)
	double   mOffset;
	float    mHue;
	uint32_t mModIdx;
	int32_t  mLen;

	static const vector<uint32_t> mMods_vect;

};
