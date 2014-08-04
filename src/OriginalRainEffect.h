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
		uint32_t birth;
		uint8_t strip;
		float hue;
		float saturation;
		uint8_t tail;
	};

	struct Hsv {
		Hsv() : h(0.0f), s(0.0f), v(0.0f) {}
		float h;
		float s;
		float v;
	};

	Hsv pixels[JellyPixel::kStrandCount][JellyPixel::kLedCount];

	static const int mDropCount = 40;
	RainDrop mDrops[mDropCount];
	float totalTime;
};