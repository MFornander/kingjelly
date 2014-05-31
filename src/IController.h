#pragma once
#include "KingJelly.h"

/**
 * Low-level abstract view of the control box. */
class IController
{
public:
	virtual ~IController() {}

	// Called every frame before calling Digital or Analog
	virtual void Update() = 0;

	// Return the state of the indicated digital input or false if the index is out of range
	virtual bool Digital(uint32_t index) const = 0;

	// Return the value of the indicated analog input or 0 if the index is out of range
	virtual float Analog(uint32_t index) const = 0;
};
