#include "global.h"

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������

/*0�ޣ�1������2�̣�3ǳ����4�죬5�ϣ�6�ƣ�7�ף�8�ң�9������10���̣�11�࣬12�ۺ죬13���ϣ�14����*/
void setColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	SetConsoleTextAttribute(hOut, ForeColor | BackGroundColor);
}

int mode = -1;//��Ϸģʽ

bool get_item = false;//��õ���
int same = 0;//��һ������͵�ǰ����ͬ��Ŀ
clock_t item_time;//������ʾʱ��

int score = 0;//�÷�
int level = 0;//��ǰ�ؿ�

bool level_up = false;
bool down_press = false;//�Ƿ��������

vector<int> colorboard = { 3,10,11,12,13,14 };
int colornum = colorboard.size();

vector<int> speed = { 750,700,650,600,550,450,400,350,300,250,200 };//���������ٶ�

vector<vector<int>> basic_score = {
	{5,6,7,8,10,12,15,18,21,25,32},
	{10,12,15,18,22,28,35,45,60,80,110},
	{4,5,6,7,8,10,12,14,16,18,22}
};//�����÷֣�ÿ��һ��ģʽ

vector<int> bonus_score = { 0, 1, 2, 4, 8 };//��������

vector<vector<int>> target_score = {
	{50,120,200,300,450,700,1000,1500,2200,3000} ,
	{60,150,300,500,800,1200,2000,3000,5000,7500},
	{60,150,250,400,600,900,1400,2000,2800,4000}
};//Ŀ�������ÿ��һ��ģʽ