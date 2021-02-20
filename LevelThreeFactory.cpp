#include "stdafx.h"
#include "LevelThreeFactory.h"
#include"LevelThree.h"

CLevelThreeFactory::CLevelThreeFactory(void)
{
}


CLevelThreeFactory::~CLevelThreeFactory(void)
{
}
shared_ptr<CStrategy> CLevelThreeFactory::FactroyCreate()
{
	shared_ptr<CStrategy> ptr(new CLevelThree);
	return ptr;
}