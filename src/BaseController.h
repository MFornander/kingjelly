#pragma once
#include "KingJelly.h"

/**
 * Low-level abstract view of the control box. */
class BaseController
{
public:
	BaseController();
	virtual ~BaseController();

	/// Called every frame before calling Digital or Analog
	virtual void Update() = 0;

	/// Return true if this controller is active
	virtual bool IsEnabled() const;

	/// Return the state of the indicated digital input or false if the index is out of range
	virtual bool Digital(uint32_t index) const;

	/// Return the value of the indicated analog input or 0 if the index is out of range
	virtual float Analog(uint32_t index) const;

protected:
	static const uint32_t kControlCount = 'z'-'a' + 1; // One channel per character
	vector<bool> mDigital; // Current state of digital channels
	vector<float> mAnalog; // Current state of analog channels
	bool mEnabled;
};
