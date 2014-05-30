/*
 * EffectManager.h
 *
 *  Created on: May 25, 2014
 *      Author: jellydev
 */

#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_

#include <vector>
#include "InputEffect.h"

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
	std::vector <InputEffect *> m_effects;
	bool                        m_switch;
	int                         m_curr_effect_idx;
};

#endif /* EFFECTMANAGER_H_ */
