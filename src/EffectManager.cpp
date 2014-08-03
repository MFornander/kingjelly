#include "EffectManager.h"
#include "PerlinRainbow.h"
#include "RainEffect.h"
#include "DefaultPixelEffect.h"


EffectManager::EffectManager() :
	mCurrentIndex(kDefaultIndex),
	mCurrentEffect(nullptr)
{
	// Add each effect's create method to our factory
	mEffectFactory.push_back(DefaultPixelEffect::Create);
	mEffectFactory.push_back(PerlinRainbow::Create);
	mEffectFactory.push_back(RainEffect::Create);

	// Instantiate the default effect
	mCurrentEffect = mEffectFactory.at(mCurrentIndex)();
}

EffectManager::~EffectManager()
{
	delete mCurrentEffect;
	mCurrentEffect = nullptr;
}

void EffectManager::ActivateEffect(uint32_t index)
{
	if (index == mCurrentIndex)
		return;

	delete mCurrentEffect;
	mCurrentIndex = index % mEffectFactory.size();
	mCurrentEffect = mEffectFactory.at(mCurrentIndex)();
}

void EffectManager::NextEffect(bool backwards)
{
	uint32_t offset = backwards ? mEffectFactory.size() - 1 : 1;
	ActivateEffect(mCurrentIndex + offset);
}

BaseEffect& EffectManager::GetActiveInstance() const
{
	return *mCurrentEffect;
}
