#include "stdafx.h"
#include "LevelTwo.h"


CLevelTwo::CLevelTwo(void)
{
	this->nLevel = 2;
}

CLevelTwo::~CLevelTwo(void)
{
}
int CLevelTwo::Analysis(CChessBorder* border,int depth,int alpa,int beta)
{
	POINT point;
	point.x = 0;
	point.y = 0;
	int Opposite;
	int Self;
	if(depth % 2 == 0)  //己方
	{
		Opposite = (this->nColor == BLACK)?WHITE:BLACK;
		Self = (this->nColor == BLACK)?BLACK:WHITE;
	}
	else 
	{        //敌方
		Opposite = this->nColor;
		Self = (this->nColor == BLACK)?WHITE:BLACK;
	}
	//获得对棋盘中自己与对方的棋局局势的判断
	int nResult_self = EvaluatePoint(border,point,Self);
	int nResult_Opposite = EvaluatePoint(border,point,Opposite);
	//若搜索深度为0，或者有一方取得胜利。则不在向下搜索。
	if(depth == 0 || nResult_self >= 80000000 || nResult_Opposite <= -200000000)
	{
		if(depth == 0)
		{
			POINTS_CHESS Best_Points;
			Best_Points = SeekPoint(border,Self);
			this->des.point.x = Best_Points.point[0].x;
			this->des.point.y = Best_Points.point[0].y;
			this->des.val = Best_Points.score[0];
			return Best_Points.score[0];
		}
		else if(nResult_self >= 80000000)
		{
			return nResult_self;
		}
		else if(nResult_Opposite <= -200000000)
		{
			return nResult_Opposite;
		}
		
	}else if(depth % 2 == 0)    //最大层，取最大，我方
	{
		CChessBorder Same_Bordered;
		//拷贝一份期盼
		for(int i=0;i<15;i++)
		{
			for(int j = 0;j<15;j++)
			{
				Same_Bordered.BorderArr[i][j] = border->BorderArr[i][j];
			}
		}
		POINTS_CHESS Best_Points;
		Best_Points = SeekPoint(&Same_Bordered,Self);

		for(int i = 0;i<5;i++)
		{
			//模拟己方落子
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = Self;
			int a = Analysis(&Same_Bordered,depth-1,alpa,beta);  
			//还原
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = 0;
			if(a > alpa)   //最优下界更新，
			{
				alpa = a;
				if(depth == 2)   //到达指定层数。选择最好的节点。
				{
					this->des.point.x = Best_Points.point[i].x;
					this->des.point.y = Best_Points.point[i].y;
					this->des.val = a;
				}
			}
			if(alpa >= beta)  //剪枝
				break;
		}
		return alpa;
	}
	else  //最小层，取最小，敌方
	{
		CChessBorder Same_Bordered;
		for(int i=0;i<15;i++)
		{
			for(int j = 0;j<15;j++)
			{
				Same_Bordered.BorderArr[i][j] = border->BorderArr[i][j];
			}
		}
		POINTS_CHESS Best_Points;
		Best_Points = SeekPoint(&Same_Bordered,Self);  
		for(int i = 0;i<5;i++)
		{
			//模拟敌方方落子
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = Self;
			int a = Analysis(&Same_Bordered,depth-1,alpa,beta);  
			//还原
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = 0;
			if(a < beta)
			{
				beta = a;
			}
			if(alpa >= beta)
				break;
		}
		return beta;
	}
}
POINTS_CHESS CLevelTwo::SeekPoint(CChessBorder* border,int color)
{
	bool B[15][15];  //用于局部搜说的二维数组
	int Worth[15][15]; //用来存储棋局中每个位置的大小。
	POINTS_CHESS bestPoint;
	POINT p;
	p.x = 0;
	p.y = 0;
	int Opposite = (this->nColor == BLACK)?WHITE:BLACK;
	//清空局部二维数组
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			 B[i][j] = 0;
		}
	}
	//搜索棋局局部范围
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			//若当前位置不为空
			if(border->BorderArr[i][j] != 0)
			{
				for(int k = -2;k<=2;k++)  //判断该八个方向上，延展两步位置可以搜索
				{
					if(i+k >=0 && i+k <15)
					{
						B[i+k][j] = true;
						if(j+k >=0 && j+k < 15)   //一三象限
							B[i+k][j+k] = true;
						if(j-k >=0 && j-k < 15)
							B[i+k][j-k] = true;   //二四象限
					}
					if(j+k >=0 && j+k < 15)
						B[i][j+k] = true;
				}
			}
		}
	}

	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			Worth[i][j] = INT_MIN;
			if(border->BorderArr[i][j] == 0 && B[i][j] == true)
			{
				border->BorderArr[i][j] = color;
				//在每一个可以下棋的位置进行评估。计算整体棋局的局势
				Worth[i][j] = EvaluatePoint(border,p,BLACK);
				Worth[i][j] += EvaluatePoint(border,p,WHITE);
				border->BorderArr[i][j] = 0;
			}
		}
	}
	//说明时最大层，要找敌人下棋位置的到最大局势点
	if(this->nColor == color)
	{
		int w = INT_MIN;
		for(int k = 0;k<5;k++)      //找到10个最优点,按照数值的大小依次排列
		{
			w = INT_MIN;
			for(int i = 0;i<15;i++)
			{
				for(int j = 0;j<15;j++)
				{
					if(Worth[i][j] > w)
					{
						w = Worth[i][j];
						bestPoint.point[k].x = i;
						bestPoint.point[k].y = j;
					}
				}
			}
			bestPoint.score[k] = w;
			Worth[bestPoint.point[k].x][bestPoint.point[k].y] = INT_MIN;
		}

		return bestPoint;
	}
	else if(this->nColor != color)   //说明时最小层，要找到我方下棋位置最小局势点
	{
		for(int i = 0;i<15;i++)
		{
			for(int j = 0;j<15;j++)
			{
				if(Worth[i][j] == INT_MIN)
				{
					Worth[i][j] = INT_MAX;
				}
			}
		}

		int w = INT_MAX;
		for(int k = 0;k<5;k++)      //找到10个最优点,按照数值的大小依次排列
		{
			w = INT_MAX;
			for(int i = 0;i<15;i++)
			{
				for(int j = 0;j<15;j++)
				{
					if(Worth[i][j] < w)
					{
						w = Worth[i][j];
						bestPoint.point[k].x = i;
						bestPoint.point[k].y = j;
					}
				}
			}
			bestPoint.score[k] = w;
			Worth[bestPoint.point[k].x][bestPoint.point[k].y] = INT_MAX;
		}

		return bestPoint;
	}
}
POINT CLevelTwo::TimeToComputer(CChessBorder* border)
{
	Analysis(border,0,INT_MIN,INT_MAX);
	border->BorderArr[des.point.x][des.point.y] = this->nColor;
	return this->des.point;
}
int CLevelTwo::EvaluatePoint(CChessBorder* border,POINT point,int color)
{
	//对当前器局进行评估。
	int nVal = 0;
	int opposite;
	if(color == WHITE)
		opposite =BLACK;
	else
		opposite = WHITE;

	for(int j = 0;j<15;j++)
	{
		for(int k = 0;k<15;k++)
		{
			point.x = j;
			point.y = k;
			for(int i = 0;i<8;i++)
			{
				//*为黑，o为白，_为当前位置
					//活4：这时必胜，无法进行对赌  ****_
					//死4：这时，若己方，则获得胜利，对方则要尽全力防守  o****_ / ***_* / **_**
					//活3：这时，再下一步，则变成活4必胜。敌方则需要去防守。_***_ / _*_**_
					//死3：这时，再下一步，仍然可以进行防守，敌方需要进攻。_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
					//活2：这时，再下一步，仍然可以防守，敌方需要进攻。_**_ / _*_*_
					//死2：这时，再下一步变死3,没啥威胁，敌方进攻就完事了。 _**o  / _*_*o  / 

				//活5 > 活4 > 死4 = 活3 > 死3 = 活2 > 死2 > 活1 > 死1

				//活5：已经胜利 *****
				if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color 
					&& GetPoint(border,point,i,4) == color
					&& GetPoint(border,point,i,5) == color)
				{
					if(this->nColor == color)  //最大层
						nVal += 80000000;
					else
						nVal += -200000000;  //最小层
				}

				//活4：这时必胜，无法进行对赌  ****_
				if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color 
					&& GetPoint(border,point,i,4) == color
					&& GetPoint(border,point,i,5) == 0)
				{
					if(this->nColor == color)
						nVal += 4000000;   //最大层
					else
						nVal += -20000000;
				}
				//死4：这时，若己方，则获得胜利，对方则要尽全力防守  o****_ 
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color
					&& GetPoint(border,point,i,4) == color
					&& GetPoint(border,point,i,5) == opposite)
				{
					if(this->nColor == color)
						nVal += 200000; 
					else
						nVal += -1000000;
				}

				//死4：这时，若己方，则获得胜利，对方则要尽全力防守  ***_*
				else if(GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color)
				{
					if(this->nColor == color)
						nVal += 200000;   
					else
						nVal += -1000000;
				}

				//活3：这时，再下一步，则变成活4必胜。敌方则需要去防守。_***_ / _*_**_
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color
					&& GetPoint(border,point,i,4) == 0)
				{
					if(this->nColor == color)
						nVal += 200000;
					else
						nVal += -1000000;
				}
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == 0
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == color
					&& GetPoint(border,point,i,-3) == 0)
				{
					if(this->nColor == color)
						nVal += 200000;
					else
						nVal += -1000000;
				}
				//死3：这时，再下一步变成死四，仍然可以进行防守，敌方需要进攻。
				//_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color
					&& GetPoint(border,point,i,4) == opposite)
				{
					if(this->nColor == color)
						nVal += 10000;
					else
						nVal += -40000;
				}
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == opposite
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == 0)
				{
					if(this->nColor == color)
						nVal += 10000;
					else
						nVal += -40000;
				}
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == opposite
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == color
					&& GetPoint(border,point,i,-3) == 0)
				{
					if(this->nColor == color)
						nVal += 10000;
					else
						nVal += -40000;
				}
				//*__** / *_*_* / o_***_o
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,-1) == 0
					&& GetPoint(border,point,i,-2) == color)
				{
					if(this->nColor == color)
						nVal += 10000;
					else
						nVal += -40000;
				}
				else if(GetPoint(border,point,i,1) == opposite
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == color
					&& GetPoint(border,point,i,-3) == color
					&& GetPoint(border,point,i,-4) == 0
					&& GetPoint(border,point,i,-5) == opposite)
				{
					if(this->nColor == color)
						nVal += 10000;
					else
						nVal += -40000;
				}
				//活2：这时，再下一步变活三，仍然可以防守，敌方需要进攻。_**_ / _*_*_
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == 0)
				{
					if(this->nColor == color)
						nVal +=10000;
					else
						nVal += -40000;
				}
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == 0
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == 0)
				{
					if(this->nColor == color)
						nVal +=10000;
					else
						nVal += -40000;
				}

				//死2：这时，再下一步变死3,没啥威胁，敌方进攻就完事了。 _**o  / _*_*o  / 
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color)
				{
					if(this->nColor == color)
						nVal +=400;
					else
						nVal += -1000;
				}
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == opposite
					&& GetPoint(border,point,i,-1) == color
					&& GetPoint(border,point,i,-2) == 0)
				{
					if(this->nColor == color)
						nVal +=400;
					else
						nVal += -1000;
				}
				//活1：下一步变为活2  __*_
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == 0)
				{
					if(this->nColor == color)
						nVal +=20;
					else
						nVal += -40;
				}
				//死1 ：下一步变为死2 __*o
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == opposite)
				{
					if(this->nColor == color)
						nVal +=1;
					else
						nVal +=-3;
				}
			}
		}
	}
	return nVal;
}
int CLevelTwo::GetPoint(CChessBorder* border,POINT point,int FX,int pos)
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