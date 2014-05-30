#ifndef ISTATE_H_
#define ISTATE_H_

#include <vector>

class IState
{
public:
	IState();
	virtual ~IState();

	bool 	Switch() const {return m_switch;}
	//void    Switch(bool val) const {m_switch = val;}

	float   Pot(unsigned int idx) const {return m_pots[idx];}
	//void    Pot(unsigned int idx, const float val){m_pots[idx] = val;}

protected:
    std::vector<float> m_pots;
	bool               m_switch;

};

#endif /* ISTATE_H_ */
