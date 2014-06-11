#pragma once
#include "KingJelly.h"

// Forwards
class JellyEffect;

/**
 * JellyEffect registrar, factory, and owner.
 *
 * Used by the main loop when switching between effects and
 * is the creater and owner of the current JellyEffect instance.
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
	void NextEffect();

	// Fetch the current JellyEffect instance
	JellyEffect& GetActiveInstance() const;

private:
	typedef JellyEffect* (*MakeEffect)();

	static const uint32_t kDefaultIndex = 1; // Startup effect index
	uint32_t              mCurrentIndex;     // Index of current JellyEffect instance
	JellyEffect*          mCurrentEffect;    // Current JellyEffect instance, never nullptr
	vector<MakeEffect>    mEffectFactory;    // List of factory methods that creates JellyEffects
};
