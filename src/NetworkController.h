#pragma once
#include "IController.h"


class NetworkController: public IController
{
public:
	NetworkController();
	virtual ~NetworkController();

	void Update();
	bool Switch() const;
//	void Switch(bool val) const;

	virtual bool Digital(uint32_t index) const;
	virtual float Analog(uint32_t index) const;

//	void Pot(unsigned int idx, const float val);

private:

	bool               m_switch;
	int                m_sock;

	vector<float> m_analog; // Current state of analog channels
};
