#pragma once
#include "factory.h"
class CLevelOneFactory :
	public CFactory
{
public:
	CLevelOneFactory(void);
	~CLevelOneFactory(void);
public:
	shared_ptr<CStrategy> FactroyCreate();
};

