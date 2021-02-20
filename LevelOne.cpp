#include "stdafx.h"
#include "LevelOne.h"


CLevelOne::CLevelOne(void)
{
	this->nLevel = 1;
}


CLevelOne::~CLevelOne(void)
{
}
POINT CLevelOne::TimeToComputer(CChessBorder* border)
{
	int nAttackVal = 0;
	POINT AttackPoint;
	int nDefendVal = 0;
	POINT DefendPoint;
	int opposite;

	if(this->nColor == BLACK)
		opposite = WHITE;
	else
		opposite = BLACK;

	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			POINT point;
			point.x = i;
			point.y = j;

			if(border->BorderArr[i][j] != 0)
				continue;
			int val = EvaluatePoint(border,point,this->nColor);
			if(val > nAttackVal)
			{
				nAttackVal = val;
				AttackPoint = point ;
			}
		}
	}

	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			POINT point;
			point.x = i;
			point.y = j;

			if(border->BorderArr[i][j] != 0)
				continue;
			int val = EvaluatePoint(border,point,opposite);
			if(val > nDefendVal)
			{
				nDefendVal = val;
				DefendPoint = point ;
			}
		}
	}
	if(nAttackVal >= nDefendVal)
	{
		border->BorderArr[AttackPoint.x][AttackPoint.y] = this->nColor;
		return AttackPoint;
	}
	if(nAttackVal < nDefendVal)
	{
		border->BorderArr[DefendPoint.x][DefendPoint.y] = this->nColor;
		return DefendPoint;
	}
}
int CLevelOne::EvaluatePoint(CChessBorder* border,POINT point,int color)
{
	//�Ե�ǰλ�ý���������
	int nVal = 0;
	int opposite;
	if(color == WHITE)
		opposite =BLACK;
	else
		opposite = WHITE;

	for(int i = 0;i<8;i++)
	{
		//*Ϊ�ڣ�oΪ�ף�_Ϊ��ǰλ��
			//��4����ʱ��ʤ���޷����жԶ�  ****_
			//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  o****_ / ***_* / **_**
			//��3����ʱ������һ�������ɻ�4��ʤ���з�����Ҫȥ���ء�_***_ / _*_**_
			//��3����ʱ������һ������Ȼ���Խ��з��أ��з���Ҫ������_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
			//��2����ʱ������һ������Ȼ���Է��أ��з���Ҫ������_**_ / _*_*_
			//��2����ʱ������һ������3,ûɶ��в���з������������ˡ� _**o  / _*_*o  / 

		//��4����ʱ��ʤ���޷����жԶ�  ****_
		if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color 
			&& GetPoint(border,point,i,4) == color
			&& GetPoint(border,point,i,5) == 0)
		{
			nVal += 4000;   //ֵ����Ϊ���
		}
		//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  o****_ 
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color
			&& GetPoint(border,point,i,4) == color
			&& GetPoint(border,point,i,5) == opposite)
		{
			nVal += 3000; 
		}

		//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  ***_*
		else if(GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color)
		{
			nVal += 3000;   
		}

		//��3����ʱ������һ�������ɻ�4��ʤ���з�����Ҫȥ���ء�_***_ / _*_**_
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color
			&& GetPoint(border,point,i,4) == 0)
		{
			nVal += 2500;
		}
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == 0
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == color
			&& GetPoint(border,point,i,-3) == 0)
		{
			nVal += 2500;
		}
		//��3����ʱ������һ��������ģ���Ȼ���Խ��з��أ��з���Ҫ������
		//_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color
			&& GetPoint(border,point,i,4) == opposite)
		{
			nVal += 2000;
		}
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == opposite
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == 0)
		{
			nVal += 2000;
		}
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == opposite
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == color
			&& GetPoint(border,point,i,-3) == 0)
		{
			nVal += 2000;
		}
		//*__** / *_*_* / o_***_o
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,-1) == 0
			&& GetPoint(border,point,i,-2) == color)
		{
			nVal += 2000;
		}
		else if(GetPoint(border,point,i,1) == opposite
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == color
			&& GetPoint(border,point,i,-3) == color
			&& GetPoint(border,point,i,-4) == 0
			&& GetPoint(border,point,i,-5) == opposite)
		{
			nVal += 2000;
		}
		//��2����ʱ������һ�����������Ȼ���Է��أ��з���Ҫ������_**_ / _*_*_
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == 0)
		{
			nVal +=1000;
		}
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == 0
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == 0)
		{
			nVal +=1000;
		}

		//��2����ʱ������һ������3,ûɶ��в���з������������ˡ� _**o  / _*_*o  / 
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color)
		{
			nVal +=500;
		}
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == opposite
			&& GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,-2) == 0)
		{
			nVal +=500;
		}
		//��1����һ����Ϊ��2  __*_
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == 0)
		{
			nVal +=300;
		}
		//��1 ����һ����Ϊ��2 __*o
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == opposite)
		{
			nVal +=200;
		}
	}

	return nVal;
}
int CLevelOne::GetPoint(CChessBorder* border,POINT point,int FX,int pos)
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