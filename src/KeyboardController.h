#pragma once
#include "BaseController.h"

/**
 * Non-blocking keyboard input controller to enable easy testing of effects.
 *
 * Digital inputs (buttons) are controlled with CAPS letters and analog
 * inputs use lowercase letters:
 * Press and hold button 0: "A1"
 * Release button 0: "A0"
 * Set potentiomenter 0 to 40%: 'a40'
 * Set potentiomenter 2 to 100%: 'c100' */
class KeyboardController : public BaseController
{
public:
	KeyboardController();
	virtual void Update();
};
