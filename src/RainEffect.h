#ifndef RAINEFFECT_H_
#define RAINEFFECT_H_

#include <lib/effect.h>

class RainEffect : public Effect
{
public:
	RainEffect();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	int   offset;
	float noise;
};

#endif /* RAINEFFECT_H_ */
