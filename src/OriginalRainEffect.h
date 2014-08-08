#pragma once
#include "BaseEffect.h"

class OriginalRainEffect : public BaseEffect
{
public:
	static BaseEffect* Create();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	OriginalRainEffect();

	struct RainDrop
	{
		float birth;
		uint8_t strip;
		float hue;
		float saturation;
		float tail;
	};

	struct Hsv {
		Hsv() : h(0.0f), s(0.0f), v(0.0f) {}
		float h;
		float s;
		float v;
	};

	Hsv pixels[JellyPixel::kStrandCount][JellyPixel::kLedCount];

	static const int kMaxDropCount = 100;
	RainDrop mDrops[kMaxDropCount];
	float totalTime;
};
