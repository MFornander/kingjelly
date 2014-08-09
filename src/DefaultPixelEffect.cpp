#include "DefaultPixelEffect.h"
#include "lib/color.h"

BaseEffect* DefaultPixelEffect::Create() {
	return new DefaultPixelEffect();
}

DefaultPixelEffect::DefaultPixelEffect() :
		mCycle(0), ledPositionBasedOnMCycle(1 / (2 * M_PI)), verticalPosition(0), color(0.5) {
	cout << "Starting DefaultPixelEffect\n";
}

void DefaultPixelEffect::beginFrame(const FrameInfo& frame) {
	color = Input(Pot1);
	acceleration = Input(Pot2);

	mCycle = fmodf(mCycle + frame.timeDelta * 4.0f, 2 * M_PI); //cycles between 0-2pi based on speed
	verticalPosition = mCycle * ledPositionBasedOnMCycle;
	//cout << verticalPosition << "\n";
	//cout << "color: " << color << "\n";
	//cout << "acceleration: " << acceleration << "\n";

}

void DefaultPixelEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {

	JellyPixel jp = JellyPixel(pixel);

	//int strand = jp.Strand();
	int led = jp.Led();
	//float verticalPosition = mCycle * ledPositionBasedOnMCycle;
	//cout << "Strand: " << strand << ". LED: " << led << "\n";
	if (led == (int) (verticalPosition * 100 * (1.0f + acceleration)))
		hsv2rgb(rgb, color, 1.0, 1.0 - verticalPosition);
}
