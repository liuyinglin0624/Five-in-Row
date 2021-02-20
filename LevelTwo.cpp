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
	if(depth % 2 == 0)  //����
	{
		Opposite = (this->nColor == BLACK)?WHITE:BLACK;
		Self = (this->nColor == BLACK)?BLACK:WHITE;
	}
	else 
	{        //�з�
		Opposite = this->nColor;
		Self = (this->nColor == BLACK)?WHITE:BLACK;
	}
	//��ö��������Լ���Է�����־��Ƶ��ж�
	int nResult_self = EvaluatePoint(border,point,Self);
	int nResult_Opposite = EvaluatePoint(border,point,Opposite);
	//���������Ϊ0��������һ��ȡ��ʤ������������������
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
		
	}else if(depth % 2 == 0)    //���㣬ȡ����ҷ�
	{
		CChessBorder Same_Bordered;
		//����һ������
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
			//ģ�⼺������
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = Self;
			int a = Analysis(&Same_Bordered,depth-1,alpa,beta);  
			//��ԭ
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = 0;
			if(a > alpa)   //�����½���£�
			{
				alpa = a;
				if(depth == 2)   //����ָ��������ѡ����õĽڵ㡣
				{
					this->des.point.x = Best_Points.point[i].x;
					this->des.point.y = Best_Points.point[i].y;
					this->des.val = a;
				}
			}
			if(alpa >= beta)  //��֦
				break;
		}
		return alpa;
	}
	else  //��С�㣬ȡ��С���з�
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
			//ģ��з�������
			Same_Bordered.BorderArr[Best_Points.point[i].x][Best_Points.point[i].y] = Self;
			int a = Analysis(&Same_Bordered,depth-1,alpa,beta);  
			//��ԭ
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
	bool B[15][15];  //���ھֲ���˵�Ķ�ά����
	int Worth[15][15]; //�����洢�����ÿ��λ�õĴ�С��
	POINTS_CHESS bestPoint;
	POINT p;
	p.x = 0;
	p.y = 0;
	int Opposite = (this->nColor == BLACK)?WHITE:BLACK;
	//��վֲ���ά����
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			 B[i][j] = 0;
		}
	}
	//������־ֲ���Χ
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			//����ǰλ�ò�Ϊ��
			if(border->BorderArr[i][j] != 0)
			{
				for(int k = -2;k<=2;k++)  //�жϸð˸������ϣ���չ����λ�ÿ�������
				{
					if(i+k >=0 && i+k <15)
					{
						B[i+k][j] = true;
						if(j+k >=0 && j+k < 15)   //һ������
							B[i+k][j+k] = true;
						if(j-k >=0 && j-k < 15)
							B[i+k][j-k] = true;   //��������
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
				//��ÿһ�����������λ�ý�������������������ֵľ���
				Worth[i][j] = EvaluatePoint(border,p,BLACK);
				Worth[i][j] += EvaluatePoint(border,p,WHITE);
				border->BorderArr[i][j] = 0;
			}
		}
	}
	//˵��ʱ���㣬Ҫ�ҵ�������λ�õĵ������Ƶ�
	if(this->nColor == color)
	{
		int w = INT_MIN;
		for(int k = 0;k<5;k++)      //�ҵ�10�����ŵ�,������ֵ�Ĵ�С��������
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
	else if(this->nColor != color)   //˵��ʱ��С�㣬Ҫ�ҵ��ҷ�����λ����С���Ƶ�
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
		for(int k = 0;k<5;k++)      //�ҵ�10�����ŵ�,������ֵ�Ĵ�С��������
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
	//�Ե�ǰ���ֽ���������
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
				//*Ϊ�ڣ�oΪ�ף�_Ϊ��ǰλ��
					//��4����ʱ��ʤ���޷����жԶ�  ****_
					//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  o****_ / ***_* / **_**
					//��3����ʱ������һ�������ɻ�4��ʤ���з�����Ҫȥ���ء�_***_ / _*_**_
					//��3����ʱ������һ������Ȼ���Խ��з��أ��з���Ҫ������_***o  / _*_**o / _**_*o / *__** / *_*_* / o_***_o
					//��2����ʱ������һ������Ȼ���Է��أ��з���Ҫ������_**_ / _*_*_
					//��2����ʱ������һ������3,ûɶ��в���з������������ˡ� _**o  / _*_*o  / 

				//��5 > ��4 > ��4 = ��3 > ��3 = ��2 > ��2 > ��1 > ��1

				//��5���Ѿ�ʤ�� *****
				if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color 
					&& GetPoint(border,point,i,4) == color
					&& GetPoint(border,point,i,5) == color)
				{
					if(this->nColor == color)  //����
						nVal += 80000000;
					else
						nVal += -200000000;  //��С��
				}

				//��4����ʱ��ʤ���޷����жԶ�  ****_
				if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == color
					&& GetPoint(border,point,i,3) == color 
					&& GetPoint(border,point,i,4) == color
					&& GetPoint(border,point,i,5) == 0)
				{
					if(this->nColor == color)
						nVal += 4000000;   //����
					else
						nVal += -20000000;
				}
				//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  o****_ 
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

				//��4����ʱ��������������ʤ�����Է���Ҫ��ȫ������  ***_*
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

				//��3����ʱ������һ�������ɻ�4��ʤ���з�����Ҫȥ���ء�_***_ / _*_**_
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
				//��3����ʱ������һ��������ģ���Ȼ���Խ��з��أ��з���Ҫ������
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
				//��2����ʱ������һ�����������Ȼ���Է��أ��з���Ҫ������_**_ / _*_*_
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

				//��2����ʱ������һ������3,ûɶ��в���з������������ˡ� _**o  / _*_*o  / 
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
				//��1����һ����Ϊ��2  __*_
				else if(GetPoint(border,point,i,1) == color
					&& GetPoint(border,point,i,2) == 0)
				{
					if(this->nColor == color)
						nVal +=20;
					else
						nVal += -40;
				}
				//��1 ����һ����Ϊ��2 __*o
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