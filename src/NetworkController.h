#pragma once
#include "BaseController.h"

class NetworkController: public BaseController
{
public:
	NetworkController();
	virtual ~NetworkController();
	virtual void Update(uint32_t seconds, bool verbose);

private:
	int   m_sock;
};
