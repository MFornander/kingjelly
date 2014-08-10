#include "SparkleMotionEffect.h"
#include "lib/color.h"

BaseEffect* SparkleMotionEffect::Create() {
	return new SparkleMotionEffect();
}

SparkleMotionEffect::SparkleMotionEffect() :
		mCycle(0), ledPositionBasedOnMCycle(1 / (2 * M_PI)), verticalPosition(
				0), color(0.5) {
	//cout << "Starting SparkleMotionEffect\n";
}

void SparkleMotionEffect::beginFrame(const FrameInfo& frame) {
	color = Input(Pot1);
	scatter = Input(Pot2);
	int scatterMax = (int) (scatter * 99.0f + 1.0f);

	mCycle = fmodf(mCycle + frame.timeDelta * 4.0f, 2 * M_PI); //cycles between 0-2pi based on speed
	verticalPosition = mCycle * ledPositionBasedOnMCycle;


	uint32_t vertInt = verticalPosition * 100;
	uint32_t vertIntSquared = vertInt * vertInt;
	for (uint32_t strand = 0; strand < JellyPixel::kStrandCount; strand++) {
		for (uint32_t led = 0; led < JellyPixel::kLedCount; led++) {
			int scatterPixels = (random() % scatterMax);
			uint32_t thisPosition = (uint32_t) ((vertIntSquared / 100) + scatterPixels);
			if (led == thisPosition) {
//				cout << "thisPosition: " << thisPosition << " vertInt: " << vertInt << "\n";
				pixels[strand][led].h = color + (scatterPixels / 400.0f);
				pixels[strand][led].s = 1.0f;
				pixels[strand][led].v = (-0.8f * vertIntSquared / 10000.0f)
						+ 1.0f;
			} else {
				pixels[strand][led].h = 0.0f;
				pixels[strand][led].s = 0.0f;
				pixels[strand][led].v = 0.0f;
			}
		}
	}

	//cout << verticalPosition << "\n";
//	cout << "color: " << color << "\n";
	//cout << "acceleration: " << acceleration << "\n";

}

void SparkleMotionEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {

	JellyPixel jp = JellyPixel(pixel);

	/*	int led = jp.Led();
	 if (led == (int) (verticalPosition * 100 * (1.0f + acceleration)))
	 hsv2rgb(rgb, color, 1.0, 1.0 - verticalPosition);
	 */
	//
	Hsv hsv = pixels[jp.Strand()][jp.Led()];

	hsv2rgb(rgb, hsv.h, hsv.s, hsv.v);
}
