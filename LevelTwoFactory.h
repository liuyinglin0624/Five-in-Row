#pragma once
#include "factory.h"
class CLevelTwoFactory :
	public CFactory
{
public:
	CLevelTwoFactory(void);
	~CLevelTwoFactory(void);
public:
	shared_ptr<CStrategy> FactroyCreate();
};

