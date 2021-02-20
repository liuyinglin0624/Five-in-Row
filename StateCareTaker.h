#pragma once
#include"StateMemento.h"
class CStateCareTaker
{
public:
	CStateCareTaker(void);
	~CStateCareTaker(void);
private:
	CStateMemento* Memento;
public:
	CStateMemento* GetMemento();
	void SetMemento(CStateMemento* menento);
};

