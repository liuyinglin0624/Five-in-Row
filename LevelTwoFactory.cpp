#include "stdafx.h"
#include "LevelTwoFactory.h"
#include"LevelTwo.h"

CLevelTwoFactory::CLevelTwoFactory(void)
{
}

CLevelTwoFactory::~CLevelTwoFactory(void)
{
}

shared_ptr<CStrategy> CLevelTwoFactory::FactroyCreate()
{
	shared_ptr<CStrategy> ptr(new CLevelTwo);
	return ptr;
}