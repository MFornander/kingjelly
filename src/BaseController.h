#pragma once
#include "KingJelly.h"

/**
 * Low-level abstract view of the control box. */
class BaseController
{
public:
	BaseController(const string& name);
	virtual ~BaseController();

	/// Called every frame before calling Digital or Analog
	virtual void Update(uint32_t seconds, bool verbose) = 0;

	/// Return the full name of this controller
	const string& GetName() const;

	/// Return true if this controller is active
	bool IsEnabled() const;

	/// Return four character tag of next effect if requested by controller
	string GetNextTag(bool reset = true);

	/// Return the state of the indicated digital input or false if the index is out of range
	inline bool Digital(uint32_t index) const { return mDigital[index]; }

	/// Return the value of the indicated analog input or 0 if the index is out of range
	inline float Analog(uint32_t index) const { return mAnalog[index]; }

	static const uint32_t kNoTag = 0  ;   // Tag returned if no effect change was requested

protected:
	static const int kControlCount = 4;   // One channel per character

	const string mName;
	bool         mEnabled;
	bool         mDigital[kControlCount]; // Current state of digital channels
	float        mAnalog[kControlCount];  // Current state of analog channels
	string       mNextEffectTag;          // Tag of next effect if not empty

};
