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
	//对当前位置进行评估。
	int nVal = 0;
	int opposite;
	if(color == WHITE)
		opposite =BLACK;
	else
		opposite = WHITE;

	for(int i = 0;i<8;i++)
	{
		//*为黑，o为白，_为当前位置
			//活4：这时必胜，无法进行对赌  ****_
			//死4：这时，若己方，则获得胜利，对方则要尽全力防守  o****_ / ***_* / **_**
			//活3：这时，再下一步，则变成活4必胜。敌方则需要去防守。_***_ / _*_**_
			//死3：这时，再下一步，仍然可以进行防守，敌方需要进攻。_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
			//活2：这时，再下一步，仍然可以防守，敌方需要进攻。_**_ / _*_*_
			//死2：这时，再下一步变死3,没啥威胁，敌方进攻就完事了。 _**o  / _*_*o  / 

		//活4：这时必胜，无法进行对赌  ****_
		if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color 
			&& GetPoint(border,point,i,4) == color
			&& GetPoint(border,point,i,5) == 0)
		{
			nVal += 4000;   //值设置为最大
		}
		//死4：这时，若己方，则获得胜利，对方则要尽全力防守  o****_ 
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color
			&& GetPoint(border,point,i,4) == color
			&& GetPoint(border,point,i,5) == opposite)
		{
			nVal += 3000; 
		}

		//死4：这时，若己方，则获得胜利，对方则要尽全力防守  ***_*
		else if(GetPoint(border,point,i,-1) == color
			&& GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == color
			&& GetPoint(border,point,i,3) == color)
		{
			nVal += 3000;   
		}

		//活3：这时，再下一步，则变成活4必胜。敌方则需要去防守。_***_ / _*_**_
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
		//死3：这时，再下一步变成死四，仍然可以进行防守，敌方需要进攻。
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
		//活2：这时，再下一步变活三，仍然可以防守，敌方需要进攻。_**_ / _*_*_
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

		//死2：这时，再下一步变死3,没啥威胁，敌方进攻就完事了。 _**o  / _*_*o  / 
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
		//活1：下一步变为活2  __*_
		else if(GetPoint(border,point,i,1) == color
			&& GetPoint(border,point,i,2) == 0)
		{
			nVal +=300;
		}
		//死1 ：下一步变为死2 __*o
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
	// 0.右  1.右上  2.上  3.左上  4.左  5.左下  6.下  7.右下。
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