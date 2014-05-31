#include "EffectManager.h"
#include "DefaultEffect.h"
#include "RainEffect.h"


EffectManager::EffectManager() :
	mCurrentIndex(kDefaultIndex),
	mCurrentEffect(nullptr)
{
	// Add each effect's create method to our factory
	mEffectFactory.push_back(DefaultEffect::Create);
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

void EffectManager::NextEffect()
{
	ActivateEffect(mCurrentIndex + 1);
	cout << "NEXT! " << mCurrentIndex << endl;
}

JellyEffect& EffectManager::GetActiveInstance() const
{
	return *mCurrentEffect;
}
