#pragma once
#include "KingJelly.h"
#include <cstdint>

/**
 * Low-level abstract view of the control box. */
class BaseController
{
public:
	BaseController(const string& name);
	virtual ~BaseController();

	/// Called every frame before calling Digital or Analog
	virtual void Update(uint32_t seconds, bool verbose) = 0;

	/// Return true if this controller is active
	const string& GetName() const;

	/// Return true if this controller is active
	bool IsEnabled() const;

	/// Return the state of the indicated digital input or false if the index is out of range
	inline bool Digital(uint32_t index) const { return mDigital[index]; }

	/// Return the value of the indicated analog input or 0 if the index is out of range
	inline float Analog(uint32_t index) const { return mAnalog[index]; }

protected:
	/// Execute a single set-input command such as "b42"
	void ExecuteCommand(const string& command);

	static const int kControlCount = 4; // One channel per character
	const string mName;
	bool         mEnabled;
	bool         mDigital[kControlCount]; // Current state of digital channels
	float        mAnalog[kControlCount];  // Current state of analog channels


};
