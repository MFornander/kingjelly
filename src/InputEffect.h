#ifndef INPUTEFFECT_H_
#define INPUTEFFECT_H_

#include "lib/effect.h"
#include "IState.h"

class InputEffect: public Effect
{
public:
	InputEffect(){};
	virtual ~InputEffect(){};

	virtual void setState(const IState&) = 0;

};

#endif /* INPUTEFFECT_H_ */
