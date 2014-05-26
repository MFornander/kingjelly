/*
 * EffectManager.h
 *
 *  Created on: May 25, 2014
 *      Author: jellydev
 */

#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_

// Forwards
class IState;
class Effect;

/// TODO
class EffectManager
{
public:
	EffectManager();
	virtual ~EffectManager();

	void SetState(const IState& state);
	Effect* GetEffect() const;

private:
};

#endif /* EFFECTMANAGER_H_ */
