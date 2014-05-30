#ifndef DEFAULTEFFECT_H_
#define DEFAULTEFFECT_H_

#include "InputEffect.h"

class DefaultEffect : public InputEffect
{
public:
	DefaultEffect();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

	void setState(const IState&){}

private:
	float mCycle;
};

#endif /* DEFAULTEFFECT_H_ */
