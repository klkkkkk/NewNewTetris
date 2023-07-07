#pragma once
#include <vector>
#include <time.h>
#include <utility>
#include <windows.h>//����̨�����Ҫͷ�ļ�

//���淽����
#define BLOCKKIND 7
//���⻭��
#define TITLE_OX 10
#define TITLE_OY 2
#define TITLE_HEIGHT 50
#define TITLE_WIDTH 50
//�����ڹ��
#define TITLE_CURSOR_X 4
#define TITLE_CURSOR_Y 14
//������
#define MAIN_OX 18
#define MAIN_OY 0
#define MAIN_HEIGHT 24
#define MAIN_WIDTH 15
//��һ�����ڴ�С
#define NEXT_HEIGHT 8
#define NEXT_WIDTH 8
//��������
#define SCORE_OX 34
#define SCORE_OY 9
#define SCORE_HEIGHT 4
#define SCORE_WIDTH 20
//���ߴ���
#define ITEM_OX 34
#define ITEM_OY 14
#define ITEM_HEIGHT 50
#define ITEM_WIDTH 50

//�������ֻ࣬��Ϊ�˷����޸���ʾ��˳����ʵÿ����Ŷ����ض��ĵ��߰󶨣����ܸ���
#define ITEM_TYPE 3
#define ITEM_1 0
#define ITEM_2 1
#define ITEM_3 2

//����Ч��
#define ITEM_1_VAL 1
#define ITEM_2_VAL 10
#define ITEM_3_VAL 3

//���߿�ݼ�
#define ITEM_1_SHORTCUT 'z'
#define ITEM_2_SHORTCUT 'x'
#define ITEM_3_SHORTCUT 'c'

//�䵽����
#define BOTTOM -2

using std::vector;
using std::pair;

extern HANDLE hOut;
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);

extern int mode;//��Ϸģʽ
extern bool get_item;//��õ���
extern int same;//�ж���һ�������Ƿ�͵�ǰ����ͬ
extern clock_t item_time;//������ʾʱ��

extern int score;//�÷�
extern int level;//��ǰ�ؿ�
extern int colornum;//��ɫ����
 
extern bool level_up;
extern bool down_press;//�Ƿ��������
 
extern vector<int> colorboard;
extern vector<int> speed;//���������ٶ�
extern vector<vector<int>> basic_score;//�����÷֣�ÿ��һ��ģʽ
extern vector<int> bonus_score;//��������
extern vector<vector<int>> target_score;//Ŀ�������ÿ��һ��ģʽ
