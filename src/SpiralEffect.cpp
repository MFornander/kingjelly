#include "SpiralEffect.h"
#include "lib/noise.h"
#include "lib/color.h"

SpiralEffect::SpiralEffect() :
		mCycle(0), ledPositionBasedOnMCycle(1 / (2 * M_PI)), verticalPosition(
				0), totalTime(0.0) {

}

void SpiralEffect::beginFrame(const FrameInfo& frame) {
	totalTime += frame.timeDelta;
	int tailLength = ((Input(Pot1) * 100.0f) / 7.0f) + 1; //max of 15
	if (tailLength == 8)
		tailLength++; //weird shit happens here so we eject.

	float color1 = Input(Pot2);
	float color2 = Input(Pot3);

//reset all pixels
	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
			pixels[strand][led].h = 0.0f;
			pixels[strand][led].s = 0.0f;
			pixels[strand][led].v = 0.0f;
		}
	}

	mCycle = fmodf(mCycle + frame.timeDelta * 32.0f, 2 * M_PI); //cycles between 0-2pi based on speed
	verticalPosition = mCycle * ledPositionBasedOnMCycle;
	int positionAround = verticalPosition * JellyPixel::kStrandCount;

	//cout << "tailLength: " << tailLength << "\n";

	for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
		for (int tailPixel = 0; tailPixel < tailLength; tailPixel++) {
			//cout << "positionAround: " << positionAround << "\n";

			positionAround = (positionAround + 1 + JellyPixel::kStrandCount)
					% JellyPixel::kStrandCount;

			float distance = tailPixel / (float) tailLength;
			float thisHue = interpolateFloat(color1, color2, distance);
			//cout << "color1: " << color1 << " color2: " << color2
			//	<< " distance: " << distance << " -> thisHue: " << thisHue
			//<< "\n";
			pixels[positionAround][led] = Hsv(thisHue, 1.0f, 1.0f);
		}
	}

}

void SpiralEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {
	JellyPixel jp = JellyPixel(pixel);

	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}

float SpiralEffect::interpolateFloat(float a, float b, float distance) {
	if (a == 1.0f)
		a = 0.0f;
	if (b == 1.0f)
		b = 0.0f;
	if (a == b) {
		return a;
	}
	float diff = a - b;

	if (diff > 0.5f) {
		float newB = 1.0f + b;
		return a + ((newB - a) * distance);
	}

	if (diff < -0.5f) {
		float newA = 1.0f + a;
		return newA - ((newA - b) * distance);
	}

	if (a > b) {
		return a - ((a - b) * distance);
	}
	return a + ((b - a) * distance);
}

