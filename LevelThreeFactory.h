#pragma once
#include "factory.h"
class CLevelThreeFactory :
	public CFactory
{
public:
	CLevelThreeFactory(void);
	~CLevelThreeFactory(void);
public:
	shared_ptr<CStrategy> FactroyCreate();
};

