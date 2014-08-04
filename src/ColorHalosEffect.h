#pragma once
#include "BaseEffect.h"

/// NOTE: Not holos anymore.  Will fix name asap.
class ColorHalosEffect: public BaseEffect
{
public:
	static BaseEffect* Create();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	ColorHalosEffect();

	// FIELDS
	int32_t mPerlinOctaves;
	float   mPosition[3];
};
