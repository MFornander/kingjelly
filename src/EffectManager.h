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

	// Set the JellyEffect with the indicated index to active
	void ActivateEffect(uint32_t index);

	// Convenience method switching to next effect or wraps to zero
	void NextEffect(bool backwards);

	// Fetch the current JellyEffect instance
	BaseEffect& GetActiveInstance() const;

private:
	typedef BaseEffect* (*MakeEffect)();

	uint32_t             mCurrentIndex;     // Index of current JellyEffect instance
	BaseEffect*          mCurrentEffect;    // Current JellyEffect instance, never nullptr
	vector<MakeEffect>   mEffectFactory;    // List of factory methods that creates JellyEffects
};
