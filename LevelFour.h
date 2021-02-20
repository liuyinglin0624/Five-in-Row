#pragma once
#include "strategy.h"
class CLevelFour :
	public CStrategy
{
public:
	CLevelFour(void);
	~CLevelFour(void);
public:
	DECISION des;
public:
	int Analysis(CChessBorder* border,int depth,int alpa,int beta);
	POINTS_CHESS SeekPoint(CChessBorder* border,int color);
public:
	POINT TimeToComputer(CChessBorder* border);
	int EvaluatePoint(CChessBorder* border,POINT point,int color);
	int GetPoint(CChessBorder* border,POINT point,int FX,int pos);
};

