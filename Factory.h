#pragma once
#include"Sys.h"
#include"Strategy.h"
class CFactory
{
public:
	CFactory(void);
	~CFactory(void);
public:
	virtual shared_ptr<CStrategy> FactroyCreate()
	{
		return NULL;
	}
};

