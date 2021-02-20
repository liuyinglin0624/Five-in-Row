#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer(void)
{
	this->hBmpSelect_B = 0;
	this->hBmpSelect_W = 0;
}

CPlayer::~CPlayer(void)
{
	DeleteObject(hBmpSelect_B);
	DeleteObject(hBmpSelect_W);
	hBmpSelect_W = 0;
	hBmpSelect_B = 0;
}

void CPlayer::SetColor(int nColor)
{
	this->nColorKey = nColor;
}
void CPlayer::SelectInit(HINSTANCE hIns)
{
	this->hBmpSelect_B = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_RECANGLE_BALCK));
	this->hBmpSelect_W = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_RECANGLE_WHITE));
}
void CPlayer::SelectShow(HDC dc)
{
	HDC hMemDC = CreateCompatibleDC(dc);
	SelectObject(hMemDC,hBmpSelect_W);
	if(x>=0 && x<15 && y>=0 && y<15)
	{
		BitBlt(dc,4+x*33,78+y*33,36,36,hMemDC,0,0,SRCAND);
		SelectObject(hMemDC,hBmpSelect_B);
		BitBlt(dc,4+x*33,78+y*33,36,36,hMemDC,0,0,SRCPAINT);
	}
	DeleteObject(hMemDC);
}
void CPlayer::GetSelectPos(POINT point)
{
	this->x = ((point.x - 19)/16)/2;
	this->y = ((point.y - 93)/16)/2;
}
BOOL CPlayer::KeyDown(POINT point,CChessBorder* border)
{
	if(border->BorderArr[point.y][point.x] == 0)
	{
		border->BorderArr[point.y][point.x] = this->nColorKey;
		return true;
	}
	return false;
}