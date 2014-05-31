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

	float Pot(unsigned int idx) const;
//	void Pot(unsigned int idx, const float val);

private:
    std::vector<float> m_pots;
	bool               m_switch;
	int                m_sock;
};
