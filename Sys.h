#pragma once

#include"resource.h"
#include<Mmsystem.h>
#include"process.h"
#include<Windows.h>
#include<memory>
using namespace std;
#pragma comment(lib,"Winmm.lib")

enum {WHITE=1,BLACK=2,OVER = 5};

#define UM_REPRANT  1024 +1

struct POINTS_CHESS
{
	POINT point[5];
	int score[5];
};

struct DECISION
{
	POINT point;
	int val;
};