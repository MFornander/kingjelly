#include "EffectManager.h"
#include "DefaultEffect.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{

}

void EffectManager::SetState(const IState&)
{
}

Effect* EffectManager::GetEffect() const
{
	static DefaultEffect defaultEffect;
	return &defaultEffect;
}
