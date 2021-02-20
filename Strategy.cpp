#include "stdafx.h"
#include "Strategy.h"


CStrategy::CStrategy(void)
{
	this->nLevel = 0;
}


CStrategy::~CStrategy(void)
{
}

void CStrategy::SetColor(int color)
{
	this->nColor = color;
}