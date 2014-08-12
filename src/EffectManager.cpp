#include "EffectManager.h"
#include "BaseEffect.h"
#include "EffectMattias.h"
#include "RainEffect.h"
#include "SparkleMotionEffect.h"
#include "OriginalRainEffect.h"
#include "RotatingWaveEffect.h"


EffectManager::EffectManager() :
	mCurrentIndex(0),
	mCurrentEffect(nullptr)

{
	#define ADD_EFFECT(name) mEffectFactory.emplace_back(name::StaticTag(), name::Create);

	// Add each effect's create method to our factory
	ADD_EFFECT(OriginalRainEffect)
	ADD_EFFECT(RotatingWaveEffect)
	ADD_EFFECT(SparkleMotionEffect)
	ADD_EFFECT(PerlinRainbow)
	ADD_EFFECT(RainEffect)
	ADD_EFFECT(ColorFlow)
	ADD_EFFECT(Glitter)
	ADD_EFFECT(Water)
	ADD_EFFECT(Swirl)
	ADD_EFFECT(SinusSnake)
	ADD_EFFECT(Fire)
	ADD_EFFECT(Particles)
	ADD_EFFECT(Beacon)
	// Add new effects here at the end to keep this list merge-easy

	// Instantiate the default effect
	SelectEffect("0000");
}

EffectManager::~EffectManager()
{
	delete mCurrentEffect;
	mCurrentEffect = nullptr;
}

void EffectManager::SelectEffect(const string& tag)
{
	// Skip if we're already on this effect
	if (mCurrentEffect != nullptr && mCurrentEffect->Tag() == tag)
		return;

	// Find the entry with the indicated tag
	auto iter = find_if(mEffectFactory.begin(), mEffectFactory.end(),
		[&tag](const EffectEntry& entry) { return entry.first == tag; });
	if (iter == mEffectFactory.end())
		return;

	mCurrentIndex = iter - mEffectFactory.begin();
	SetActiveInstance(iter->second());

}

void EffectManager::NextEffect(bool backwards)
{
	mCurrentIndex += backwards ? mEffectFactory.size() - 1 : 1;
	mCurrentIndex = mCurrentIndex % mEffectFactory.size();
	SetActiveInstance(mEffectFactory.at(mCurrentIndex).second());
}

void EffectManager::SetActiveInstance(BaseEffect* effect)
{
	if (effect == mCurrentEffect || effect == nullptr)
		return;

	fprintf(stdout, "New Effect: %s\n", effect->FullName().c_str());
	delete mCurrentEffect;
	mCurrentEffect = effect;
}

BaseEffect& EffectManager::GetActiveInstance() const
{
	return *mCurrentEffect;
}
