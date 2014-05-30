#ifndef NETWORKSTATE_H_
#define NETWORKSTATE_H_

#include "IState.h"

class NetworkState: public IState
{
public:
	NetworkState();
	virtual ~NetworkState();

	void Update();

private:
	int m_sock;
};

#endif /* NETWORKSTATE_H_ */
