#include "EffectManager.h"
#include "DefaultEffect.h"
#include "RainEffect.h"


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
	static RainEffect    rainEffect;
	return &rainEffect;
}
