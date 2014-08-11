#pragma once
#include "BaseEffect.h"

class RotatingWaveEffect: public BaseEffect {
public:
	static BaseEffect* Create();  // Required factory method for all effects

	virtual void beginFrame(const FrameInfo& frame); // Called once per frame
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const; // Called once per LED

private:
	RotatingWaveEffect(); // Private ctor forcing factory-only contruction

	// FIELDS
	float color;

	float interpolateFloat(float a, float b, float distance);

	float totalTime;

	struct Hsv {
		Hsv() :
				h(0.0f), s(0.0f), v(0.0f) {
		}
		Hsv(float h, float s, float v) :
				h(h), s(s), v(v) {
		}

		float h;
		float s;
		float v;
	};

	//Hsv interpolate(Hsv a, Hsv b, float distance);

	Hsv pixels[JellyPixel::kStrandCount][JellyPixel::kLedCount];

	Hsv interpolate(Hsv a, Hsv b, float distance) {
		Hsv result = Hsv();
		result.h = interpolateFloat(a.h, b.h, distance);
		result.s = interpolateFloat(a.s, b.s, distance);
		result.v = interpolateFloat(a.v, b.v, distance);
		return result;
	}
};
