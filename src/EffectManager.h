#pragma once
#include "KingJelly.h"
#include <vector>

// Forwards
class BaseEffect;

/**
 * JellyEffect registrar, factory, and owner.
 *
 * Used by the main loop when switching between effects and
 * is the creator and owner of the current JellyEffect instance.
 * JellyEffects are created and destroyed to keep memory usage low
 * in anticipation of many effects classes with potentially heavy
 * field variables. */
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	// Set the JellyEffect with the indicated tag to active
	void SelectEffect(const string& tag);

	// Convenience method switching to next effect or wraps to zero
	void NextEffect(bool backwards);

	// Fetch the current JellyEffect instance
	BaseEffect& GetActiveInstance();

private:
	void SetActiveInstance(BaseEffect* effect);

	uint32_t       mCurrentIndex;          // Current effect index in factor
	BaseEffect*    mCurrentEffect;         // Current JellyEffect instance, never nullptr
	typedef BaseEffect* (*MakeEffect)();
	typedef pair<string,MakeEffect> EffectEntry;
	vector<EffectEntry>  mEffectFactory;  // Map of factory methods that create JellyEffects
};
