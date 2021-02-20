#include "stdafx.h"
#include "LevelOneFactory.h"
#include"LevelOne.h"

CLevelOneFactory::CLevelOneFactory(void)
{
}


CLevelOneFactory::~CLevelOneFactory(void)
{
}
shared_ptr<CStrategy> CLevelOneFactory::FactroyCreate()
{
	shared_ptr<CStrategy> ptr(new CLevelOne);
	return ptr;
}