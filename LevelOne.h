#pragma once
#include "strategy.h"
class CLevelOne :
	public CStrategy
{
public:
	CLevelOne(void);
	~CLevelOne(void);
public:
	POINT TimeToComputer(CChessBorder* border);
	int EvaluatePoint(CChessBorder* border,POINT point,int color);
	int GetPoint(CChessBorder* border,POINT point,int FX,int pos);
};

