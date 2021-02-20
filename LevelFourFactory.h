#pragma once
#include "factory.h"
class CLevelFourFactory :
	public CFactory
{
public:
	CLevelFourFactory(void);
	~CLevelFourFactory(void);
public:
	shared_ptr<CStrategy> FactroyCreate();
};

