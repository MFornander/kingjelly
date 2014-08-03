#include "DefaultPixelEffect.h"
#include "lib/noise.h"
#include "lib/color.h"

BaseEffect* DefaultPixelEffect::Create() {
	return new DefaultPixelEffect();
}

DefaultPixelEffect::DefaultPixelEffect() :
	mCycle(0)
//	mSaturation(0)
{}

void DefaultPixelEffect::beginFrame(const FrameInfo& frame) {
	const float speed = 1.0f;// Input(0) * 4.0f;
	mCycle = fmodf(mCycle + frame.timeDelta * speed, 2 * M_PI); //cycles between 0-2pi based on speed
    verticalPosition = mCycle * ledPositionBasedOnMCycle;

}

void DefaultPixelEffect::shader(Vec3& rgb, const PixelInfo& pixel) const {

	JellyPixel jp = JellyPixel(pixel);

	int strand = jp.Strand();
	int led = jp.Led();
	//float verticalPosition = mCycle * ledPositionBasedOnMCycle;
//	cout << "Strand: " << strand << ". LED: " << led << "\n";
//    cout << mCycle << "\n";
	if (led == (int) (verticalPosition * 100))
		hsv2rgb(rgb, 0.5, 1.0, 1.0 - verticalPosition);
//	else
//		hsv2rgb(rgb, 1.0, 1.0, 1.0);
}
