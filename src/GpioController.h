#pragma once
#include "IController.h"
#include "lib/GPIO/GPIOManager.h"

/**
 * TODO */
class GpioController : public IController
{
public:
	GpioController();

	virtual void Update();
	virtual bool Digital(uint32_t index) const;
	virtual float Analog(uint32_t index) const;

private:
	static const uint32_t kControlCount = 4;
	vector<bool> mDigital; // Current state of digital channels
	vector<float> mAnalog; // Current state of analog channels

	GPIO::GPIOManager* mGpio;
};
