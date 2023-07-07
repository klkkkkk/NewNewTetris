#include "global.h"

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄

/*0无，1深蓝，2绿，3浅蓝，4红，5紫，6黄，7白，8灰，9天蓝，10亮绿，11青，12粉红，13真紫，14淡黄*/
void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	SetConsoleTextAttribute(hOut, ForeColor | BackGroundColor);
}

int mode = -1;//游戏模式

bool get_item = false;//获得道具
int same = 0;//下一个方块和当前的相同数目
clock_t item_time;//道具提示时间

int score = 0;//得分
int level = 0;//当前关卡

bool level_up = false;
bool down_press = false;//是否加速下落

vector<int> colorboard = { 3,10,11,12,13,14 };
int colornum = colorboard.size();

vector<int> speed = { 750,700,650,600,550,450,400,350,300,250,200 };//方块下落速度

vector<vector<int>> basic_score = {
	{5,6,7,8,10,12,15,18,21,25,32},
	{10,12,15,18,22,28,35,45,60,80,110},
	{4,5,6,7,8,10,12,14,16,18,22}
};//基础得分，每行一种模式

vector<int> bonus_score = { 0, 1, 2, 4, 8 };//多消倍率

vector<vector<int>> target_score = {
	{50,120,200,300,450,700,1000,1500,2200,3000} ,
	{60,150,300,500,800,1200,2000,3000,5000,7500},
	{60,150,250,400,600,900,1400,2000,2800,4000}
};//目标分数，每行一种模式