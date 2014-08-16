#include "RotatingWaveEffect.h"
#include "lib/noise.h"
#include "lib/color.h"

RotatingWaveEffect::RotatingWaveEffect() :
		totalTime(0.0), waveCount(2) {

	for (int i = 0; i < maxWaves; i++) {
		wavePeriods[i] = (random() % 40) / 100.0f + 0.5f;
//		cout << "wavePeriod " << i << ": " << wavePeriods[i] << "\n";
	}

}

void RotatingWaveEffect::beginFrame(const FrameInfo& frame) {
	totalTime += frame.timeDelta;

	if (InputClicked(JoyUp))
		if (waveCount < 9)
			waveCount++;
	if (InputClicked(JoyDown))
		if (waveCount > 1)
			waveCount--;

//reset all pixels
	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
			pixels[strand][led].h = 0.0f;
			pixels[strand][led].s = 0.0f;
			pixels[strand][led].v = 0.0f;
		}
	}

	float baseColor = Input(Pot1);
	float increment = (Input(Pot2) + 0.1f) / 3.0f / waveCount;
	for (int i = 0; i < waveCount; i++) {
		waveColors[i] = Hsv(baseColor + i * increment, 1.0f, 1.0f);
	}

	int tailCount = 14 - waveCount; // (int) (Input(Pot3) * 10.0f);
	//cout << "tailCount: " << tailCount << "\n";

	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		float offset = ((2 * M_PI) / JellyPixel::kStrandCount) * strand;

		for (int i = 0; i < waveCount; i++) {
			float wavePosition = totalTime / wavePeriods[i];

			int divider = (100 / (waveCount + 1));
			float upOrDown = cos(wavePosition + offset);

			int waveY = (int) (divider + (i * divider)
					+ (sin(wavePosition + offset) * divider));

			//		cout << "waveY: " << waveY << " upOrDown: " << upOrDown << "\n";

			Hsv thisColor = waveColors[i];
			pixels[strand][waveY] = thisColor;

			float fadeIncr = 0.9f / tailCount;
			if (upOrDown > 0.15) { //led is on its way up in numbers/down the jelly
				for (int j = 0; j < tailCount; j++) {
					if (waveY - j > 0) {
						pixels[strand][waveY - j] = Hsv(thisColor.h,
								thisColor.s, 1.0f - fadeIncr - fadeIncr * j);
					}
				}
			} else if (upOrDown < -0.15) { //led is on its way down in numbers/up the jelly
				for (int j = 0; j < tailCount; j++) {
					if (waveY + j < JellyPixel::kLedCount) {
						pixels[strand][waveY + j] = Hsv(thisColor.h,
								thisColor.s, 1.0f - fadeIncr - fadeIncr * j);
					}
				}
			}
		}
	}
}

void RotatingWaveEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {
	JellyPixel jp = JellyPixel(pixel);

	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}

float RotatingWaveEffect::interpolateFloat(float a, float b, float distance) {
	if (a == b) {
		return a;
	}
	if (a > b) {
		return a - ((a - b) * distance);
	}
	return a + ((b - a) * distance);
}

