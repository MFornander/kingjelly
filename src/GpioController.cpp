#include "GpioController.h"
#include "lib/GPIO/GPIOConst.h"


GpioController::GpioController() :
	mDigital(kControlCount),
	mAnalog(kControlCount),
	mGpio(GPIO::GPIOManager::getInstance())
{
	int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_18");
	mGpio->exportPin(pin);
	mGpio->setDirection(pin, GPIO::INPUT);
}

void GpioController::Update()
{
	int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P8_18");
	mDigital.at(0) = mGpio->getValue(pin) == GPIO::HIGH;
}

bool GpioController::Digital(uint32_t index) const
{
	if (index < mDigital.size())
		return mDigital.at(index);
	return false;
}

float GpioController::Analog(uint32_t index) const
{
	if (index < mAnalog.size())
		return mAnalog.at(index);
	return 0;
}
