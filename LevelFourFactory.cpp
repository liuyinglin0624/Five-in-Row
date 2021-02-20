#include "stdafx.h"
#include "LevelFourFactory.h"
#include"LevelFour.h"

CLevelFourFactory::CLevelFourFactory(void)
{
}


CLevelFourFactory::~CLevelFourFactory(void)
{
}
shared_ptr<CStrategy> CLevelFourFactory::FactroyCreate()
{
	shared_ptr<CStrategy> ptr(new CLevelFour);
	return ptr;
}