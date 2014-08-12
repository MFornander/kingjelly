#pragma once
#include "BaseEffect.h"

EFFECT(D002, SparkleMotionEffect)
	float mCycle;
	float ledPositionBasedOnMCycle;
	float verticalPosition;
	float color;
	float scatter;

	struct Hsv {
		Hsv() :
				h(0.0f), s(0.0f), v(0.0f) {
		}
		float h;
		float s;
		float v;
	};

	Hsv pixels[JellyPixel::kStrandCount][JellyPixel::kLedCount];

	float totalTime;
};
