#pragma once
#include"ChessBorder.h"
#include"Sys.h"
class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);
public:
	HBITMAP hBmpSelect_W;
	HBITMAP hBmpSelect_B;
	int x;
	int y;
	int nColorKey;
public:
	void SetColor(int nColor);
	void SelectInit(HINSTANCE hIns);
	void SelectShow(HDC dc);
	void GetSelectPos(POINT point);
	BOOL KeyDown(POINT point,CChessBorder* border);
};

