#pragma once
#include <vector>
#include <time.h>
#include <utility>
#include <windows.h>//控制台编程主要头文件

//常规方块数
#define BLOCKKIND 7
//标题画面
#define TITLE_OX 10
#define TITLE_OY 2
#define TITLE_HEIGHT 50
#define TITLE_WIDTH 50
//标题内光标
#define TITLE_CURSOR_X 4
#define TITLE_CURSOR_Y 14
//主界面
#define MAIN_OX 18
#define MAIN_OY 0
#define MAIN_HEIGHT 24
#define MAIN_WIDTH 15
//下一个窗口大小
#define NEXT_HEIGHT 8
#define NEXT_WIDTH 8
//分数窗口
#define SCORE_OX 34
#define SCORE_OY 9
#define SCORE_HEIGHT 4
#define SCORE_WIDTH 20
//道具窗口
#define ITEM_OX 34
#define ITEM_OY 14
#define ITEM_HEIGHT 50
#define ITEM_WIDTH 50

//道具种类，只是为了方便修改显示的顺序，其实每个编号都与特定的道具绑定，不能更改
#define ITEM_TYPE 3
#define ITEM_1 0
#define ITEM_2 1
#define ITEM_3 2

//道具效果
#define ITEM_1_VAL 1
#define ITEM_2_VAL 10
#define ITEM_3_VAL 3

//道具快捷键
#define ITEM_1_SHORTCUT 'z'
#define ITEM_2_SHORTCUT 'x'
#define ITEM_3_SHORTCUT 'c'

//落到地面
#define BOTTOM -2

using std::vector;
using std::pair;

extern HANDLE hOut;
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);

extern int mode;//游戏模式
extern bool get_item;//获得道具
extern int same;//判断下一个方块是否和当前的相同
extern clock_t item_time;//道具提示时间

extern int score;//得分
extern int level;//当前关卡
extern int colornum;//颜色总数
 
extern bool level_up;
extern bool down_press;//是否加速下落
 
extern vector<int> colorboard;
extern vector<int> speed;//方块下落速度
extern vector<vector<int>> basic_score;//基础得分，每行一种模式
extern vector<int> bonus_score;//多消倍率
extern vector<vector<int>> target_score;//目标分数，每行一种模式
