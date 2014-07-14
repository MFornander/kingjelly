#pragma once
#include "BaseController.h"

class NetworkController: public BaseController
{
public:
	NetworkController();
	virtual ~NetworkController();
	virtual void Update();

private:
	int   m_sock;
};
