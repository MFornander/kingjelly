#include "EffectManager.h"
#include "DefaultEffect.h"
#include "RainEffect.h"

#include <vector>

EffectManager::EffectManager():
	m_switch(false),
	m_curr_effect_idx(0)
{
	m_effects.push_back(new RainEffect); 
	m_effects.push_back(new DefaultEffect); 
}

EffectManager::~EffectManager()
{

}

void EffectManager::SetState(const IState& state)
{
	if(state.Switch() != m_switch)
	{
		m_curr_effect_idx = (m_curr_effect_idx+1)%m_effects.size();
		m_switch = state.Switch();
	}

	m_effects[0]->setState(state);
}

Effect* EffectManager::GetEffect() const
{
	return(static_cast<Effect *>(m_effects[m_curr_effect_idx]));
}
