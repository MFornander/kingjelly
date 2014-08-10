#include "RotatingWaveEffect.h"
#include "lib/color.h"

BaseEffect* RotatingWaveEffect::Create() {
	return new RotatingWaveEffect();
}

RotatingWaveEffect::RotatingWaveEffect() :
		color(0.5), totalTime(0.0)  {
}

void RotatingWaveEffect::beginFrame(const FrameInfo& frame) {
	totalTime += frame.timeDelta;

	float topColor = 0.0f;
	float topWaveColor = 0.33f;
	float bottomWaveColor = 0.66f;
	float bottomColor = 1.0f;

	//reset all pixels
	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
			pixels[strand][led].h = 0.0f;
			pixels[strand][led].s = 0.0f;
			pixels[strand][led].v = 0.0f;
		}
	}

	float topWavePeriod = 0.1f + Input(Pot1);
	float bottomWavePeriod = 0.1f + Input(Pot2);

	float topWavePosition = totalTime / topWavePeriod;
	float bottomWavePosition = totalTime / bottomWavePeriod;

	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		float offset = ((2 * M_PI) / JellyPixel::kStrandCount) * strand;

		int topWaveY = (int) (24 + (sin(topWavePosition + offset) * 25.0f));
		int bottomWaveY =
				(int) (74 + (sin(bottomWavePosition + offset) * 25.0f));

		pixels[strand][topWaveY].h = topWaveColor;
		pixels[strand][topWaveY].s = 1.0f;
		pixels[strand][topWaveY].v = 1.0f;

		pixels[strand][bottomWaveY].h = bottomWaveColor;
		pixels[strand][bottomWaveY].s = 1.0f;
		pixels[strand][bottomWaveY].v = 1.0f;

		for (float gradientY = 0.0f; gradientY < topWaveY; gradientY++) {
			float distance = gradientY / ((float) topWaveY);
			float interpolatedColor = interpolate(topColor,topWaveColor, distance);
			cout << "topWaveY: " << topWaveY << " gradientY: " << gradientY << " distance: " << distance << " interpolatedColor: " << interpolatedColor << "\n";
			pixels[strand][(int) gradientY].h = interpolatedColor;
			pixels[strand][(int) gradientY].s = 1.0f;
			pixels[strand][(int) gradientY].v = 1.0f;
//		 jellyImage.setColor((int) gradientY, (int) i, topColor.interpolate(topWaveColor, gradientY / topWaveY));
		}

		/*
		 for (float gradientY = topWaveY + 1; gradientY < bottomWaveY; gradientY++) {
		 jellyImage.setColor((int) gradientY, (int) i, topWaveColor.interpolate(bottomWaveColor, (gradientY - topWaveY) / (bottomWaveY - topWaveY)));
		 }

		 for (float gradientY = bottomWaveY + 1; gradientY < _100; gradientY++) {
		 jellyImage.setColor((int) gradientY, (int) i, bottomWaveColor.interpolate(bottomColor, (gradientY - bottomWaveY) / (_100 - bottomWaveY)));
		 }
		 */
	}
}

void RotatingWaveEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {
	JellyPixel jp = JellyPixel(pixel);

	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}

float RotatingWaveEffect::interpolate(float a, float b, float distance) {
	if (a == b) {
		return a;
	}
	if (a > b) {
		return b + ((a - b) * distance);
	}

	return a + ((b - a) * distance);
}

