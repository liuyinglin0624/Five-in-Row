#include "stdafx.h"
#include "StateMemento.h"


CStateMemento::CStateMemento(void)
{
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			arr[i][j] = 0;
		}
	}
}


CStateMemento::~CStateMemento(void)
{
}
