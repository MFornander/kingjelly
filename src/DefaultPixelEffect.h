#pragma once
#include "BaseEffect.h"


class DefaultPixelEffect : public BaseEffect
{
public:
	static BaseEffect* Create();  // Required factory method for all effects

	virtual void beginFrame(const FrameInfo& frame); // Called once per frame
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const; // Called once per LED

private:
	DefaultPixelEffect(); // Private ctor forcing factory-only contruction

	// FIELDS
	float mCycle;
    float ledPositionBasedOnMCycle;
    float verticalPosition;
};
