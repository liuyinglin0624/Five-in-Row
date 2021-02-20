#pragma once
#include"Sys.h"
class CChessBorder
{
public:
	CChessBorder(void);
	~CChessBorder(void);
public:
	HBITMAP hBmpBorder;
	int BorderArr[15][15];
	HBITMAP hBmpBlackKey_B;
	HBITMAP hBmpBlackKey_W;
	HBITMAP hBmpWhiteKey_W;
	HBITMAP hBmpWhiteKey_B;
public:
	void ChessBorderInit(HINSTANCE hIns);
	void ChessBorderShow(HDC dc);
	void Clear();
};

