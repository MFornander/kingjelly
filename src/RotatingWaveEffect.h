#pragma once
#include "BaseEffect.h"

class RotatingWaveEffect: public BaseEffect {
public:
	static BaseEffect* Create();  // Required factory method for all effects

	virtual void beginFrame(const FrameInfo& frame); // Called once per frame
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const; // Called once per LED

private:
	RotatingWaveEffect(); // Private ctor forcing factory-only contruction
	float interpolate(float a, float b, float distance);

	// FIELDS
	float color;

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
