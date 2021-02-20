#include "stdafx.h"
#include "StateCareTaker.h"


CStateCareTaker::CStateCareTaker(void)
{
	this->Memento = NULL;
}


CStateCareTaker::~CStateCareTaker(void)
{
	delete this->Memento;
}
CStateMemento* CStateCareTaker::GetMemento()
{
	return this->Memento;
}
void CStateCareTaker::SetMemento(CStateMemento* menento)
{
	this->Memento = menento;
}

