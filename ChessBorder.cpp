#include "stdafx.h"
#include "ChessBorder.h"


CChessBorder::CChessBorder(void)
{
	this->hBmpBorder = 0;
	FILE* pF;
	fopen_s(&pF,"..\\res\\Border.txt","rb");

	char txt;
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			if((txt = fgetc(pF))!= EOF )
			{
				this->BorderArr[i][j] = txt - '0';
			}
		}
		fgetc(pF);
		fgetc(pF);
	}
	int aa = 10;
	fclose(pF);
}


CChessBorder::~CChessBorder(void)
{
	DeleteObject(hBmpBorder);
	hBmpBorder = 0;
}

void CChessBorder::ChessBorderInit(HINSTANCE hIns)
{
	this->hBmpBorder = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BORDER));
	this->hBmpBlackKey_B = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BLACKKEY_BLACK));
	this->hBmpBlackKey_W = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BALCKKEY_WHITE));
	this->hBmpWhiteKey_B = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WHITEKRY_BLACK));
	this->hBmpWhiteKey_W = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WHITEKEY_WHITE));
}
void CChessBorder::ChessBorderShow(HDC dc)
{
	HDC hMemDC = CreateCompatibleDC(dc);
	SelectObject(hMemDC,this->hBmpBorder);
	BitBlt(dc,0,0,501,614,hMemDC,0,0,SRCCOPY);
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			if(this->BorderArr[i][j] == 1)
			{
				SelectObject(hMemDC,this->hBmpWhiteKey_W);
				BitBlt(dc,4+j*33,78+i*33,30,30,hMemDC,0,0,SRCAND);
				SelectObject(hMemDC,this->hBmpWhiteKey_B);
				BitBlt(dc,4+j*33,78+i*33,30,30,hMemDC,0,0,SRCPAINT);
			}
			else if(this->BorderArr[i][j] == 2)
			{
				SelectObject(hMemDC,this->hBmpBlackKey_W);
				BitBlt(dc,4+j*33,78+i*33,30,30,hMemDC,0,0,SRCAND);
				SelectObject(hMemDC,this->hBmpBlackKey_B);
				BitBlt(dc,4+j*33,78+i*33,30,30,hMemDC,0,0,SRCPAINT);
			}
		}
	}
	DeleteDC(hMemDC);
}
void CChessBorder::Clear()
{
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			this->BorderArr[i][j] = 0;
		}
	}
}