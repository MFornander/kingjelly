#pragma once
#include "IController.h"

/**
 * Non-blocking keyboard input controller to enable easy testing of effects.
 *
 * Digital inputs (buttons) are controlled with CAPS letters and analog
 * inputs use lowercase letters:
 * Press and hold button 0: "A1"
 * Release button 0: "A0"
 * Set potentiomenter 0 to 40%: 'a40'
 * Set potentiomenter 2 to 100%: 'c100' */
class KeyboardController : public IController
{
public:
	KeyboardController();
	virtual ~KeyboardController();

	// Refresh all channels by processing stdin lines since last Update call
	virtual void Update();

	virtual bool Digital(uint32_t index) const;
	virtual float Analog(uint32_t index) const;

private:
	// Execute a single set-input command such as "B42"
	void ExecuteCommand(const string& command);

	static const uint32_t kControlCount = 'z'-'a' + 1; // One channel per character
	vector<bool> mDigital; // Current state of digital channels
	vector<float> mAnalog; // Current state of analog channels
};
