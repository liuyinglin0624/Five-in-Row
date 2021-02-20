#pragma once
#include"ChessBorder.h"
#include"Sys.h"
class CJudgement
{
public:
	CJudgement(void);
	~CJudgement(void);
public:
	bool IsWin(CChessBorder* border,int nColor,POINT point);
	bool IsFiveKey(CChessBorder* border,int nColor,POINT point);
	int GetPoint(CChessBorder* border,POINT point,int FX,int pos);
};

