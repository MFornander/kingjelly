#pragma once
#include "BaseController.h"

/**
 * TODO: Implement a controller that switches effects automatically
 * when all other controllers are dead. */
class AutoController: public BaseController
{
public:
	AutoController();
	virtual void Update();
};
