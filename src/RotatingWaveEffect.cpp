#include "RotatingWaveEffect.h"
#include "lib/color.h"

BaseEffect* RotatingWaveEffect::Create() {
	return new RotatingWaveEffect();
}

RotatingWaveEffect::RotatingWaveEffect() :
		color(0.5), totalTime(0.0)  {
}

void RotatingWaveEffect::beginFrame(const FrameInfo& frame) {

	//reset all pixels
	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
			pixels[strand][led].h = 0.0f;
			pixels[strand][led].s = 0.0f;
			pixels[strand][led].v = 0.0f;
		}
	}

	totalTime += frame.timeDelta;

	float topWavePeriod = 0.1f + Input(Pot1);
	float bottomWavePeriod = 0.1f + Input(Pot2);

	float topWavePosition = totalTime / topWavePeriod;
	float bottomWavePosition = totalTime / bottomWavePeriod;

	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		float offset = ((2 * M_PI) / JellyPixel::kStrandCount) * strand;

		int topWaveY = (int) (24 + (sin(topWavePosition + offset) * 25.0f));
		int bottomWaveY =
				(int) (74 + (sin(bottomWavePosition + offset) * 25.0f));

		pixels[strand][topWaveY].h = 0.0f;
		pixels[strand][topWaveY].s = 1.0f;
		pixels[strand][topWaveY].v = 1.0f;

		pixels[strand][bottomWaveY].h = 0.5f;
		pixels[strand][bottomWaveY].s = 1.0f;
		pixels[strand][bottomWaveY].v = 1.0f;
	}
}

void RotatingWaveEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {
	JellyPixel jp = JellyPixel(pixel);

	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}
