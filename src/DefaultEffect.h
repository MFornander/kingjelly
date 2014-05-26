#ifndef DEFAULTEFFECT_H_
#define DEFAULTEFFECT_H_

#include <lib/effect.h>

class DefaultEffect : public Effect
{
public:
	DefaultEffect();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

private:
	float mCycle;
};

#endif /* DEFAULTEFFECT_H_ */
