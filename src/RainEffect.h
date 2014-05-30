#ifndef RAINEFFECT_H_
#define RAINEFFECT_H_

#include "InputEffect.h"
#include "IState.h"


class RainEffect : public InputEffect
{
public:
	RainEffect();

	virtual void beginFrame(const FrameInfo& frame);
	virtual void shader(Vec3& rgb, const PixelInfo& pixel) const;

	virtual void setState(const IState& state);


private:
	int   offset;
	float noise;
	float hue;
};

#endif /* RAINEFFECT_H_ */
