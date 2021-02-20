#pragma once
#include"ChessBorder.h"
class CStrategy
{
public:
	CStrategy(void);
	~CStrategy(void);
public:
	int nColor;
	int nLevel;
public:
	void SetColor(int color);
public:
	virtual POINT TimeToComputer(CChessBorder* border)
	{
		POINT a;
		a.x = 0;
		a.y = 0;
		return a;
	}
	virtual int EvaluatePoint(CChessBorder* border,POINT point,int color){
	return 0;
	}
	virtual int GetPoint(CChessBorder* border,POINT point,int color,int FX)
	{
	return 0;
	}
};

