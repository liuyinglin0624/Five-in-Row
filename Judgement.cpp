#include "stdafx.h"
#include "Judgement.h"


CJudgement::CJudgement(void)
{
}


CJudgement::~CJudgement(void)
{
}
bool CJudgement::IsWin(CChessBorder* border,int nColor,POINT point)
{
	if(border == NULL)
		return false;
	if(IsFiveKey(border,nColor,point) == true)
		return true;
	else
		return false;
}
bool CJudgement::IsFiveKey(CChessBorder* border,int nColor,POINT point)
{
	if(border == NULL)
		return false;

	//������������ж����������������  *Ϊ���ӡ�_Ϊ��ǰλ��
	//��һ�����****_
	//�ڶ������***_*
	//���������**_**
	for(int i = 0;i<8;i++)
	{
		//��һ�����****_
		if(GetPoint(border,point,i,1)  == GetPoint(border,point,i,2) && 
			GetPoint(border,point,i,2)  == GetPoint(border,point,i,3) && 
			GetPoint(border,point,i,3) == GetPoint(border,point,i,4) && 
			GetPoint(border,point,i,4) == nColor)
		{
			return true;
		}
		//�ڶ������***_*
		if(GetPoint(border,point,i,-1) == GetPoint(border,point,i,1) 
			&& GetPoint(border,point,i,1) == GetPoint(border,point,i,2) 
			 && GetPoint(border,point,i,2) == GetPoint(border,point,i,3) 
			  && GetPoint(border,point,i,3)  == nColor)
		{
			return true;
		}
		//���������**_**
		if(GetPoint(border,point,i,-2) == GetPoint(border,point,i,-1) 
			&& GetPoint(border,point,i,-1) == GetPoint(border,point,i,1) 
			&& GetPoint(border,point,i,1) == GetPoint(border,point,i,2) 
			&& GetPoint(border,point,i,2) == nColor)
		{
			return true;
		}
	}
	return false;
}
int CJudgement::GetPoint(CChessBorder* border,POINT point,int FX,int pos)
{
	// 0.��  1.����  2.��  3.����  4.��  5.����  6.��  7.���¡�
	int x = point.x;
	int y = point.y;
	int nCurrent_x;
	int nCurrent_y;
	if(FX == 0)
	{
		nCurrent_x = x;
		nCurrent_y = y+pos;
	}
	if(FX == 1)
	{
		nCurrent_x = x-pos;
		nCurrent_y = y+pos;
	}
	if(FX == 2)
	{
		nCurrent_x = x-pos;
		nCurrent_y = y;
	}
	if(FX == 3)
	{
		nCurrent_x = x-pos;
		nCurrent_y = y-pos;
	}
	if(FX == 4)
	{
		nCurrent_x = x;
		nCurrent_y = y-pos;
	}
	if(FX == 5)
	{
		nCurrent_x = x+pos;
		nCurrent_y = y-pos;
	}
	if(FX == 6)
	{
		nCurrent_x = x+pos;
		nCurrent_y = y;
	}
	if(FX == 7)
	{
		nCurrent_x = x+pos;
		nCurrent_y = y+pos;
	}
	if(nCurrent_x<0 || nCurrent_x >15 || nCurrent_y <0 || nCurrent_y > 15)
	{
		return OVER;
	}
	else
	{
		return border->BorderArr[nCurrent_x][nCurrent_y];
	}
}