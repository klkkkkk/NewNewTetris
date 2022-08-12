#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>//getch()函数
#include <stdlib.h>//system()函数
#include <time.h>
#include "block.h"
#include "draw.h"
#include "action.h"
#include "check.h"
#include "constant.h"
using namespace std;

extern void scene_title();

int mode = -1;//游戏模式
int score = 0;//得分
int speed[] = { 750,700,650,600,550,450,400,350,300,250,200 };//方块下落速度
int basic_score[3][11] = {
	{5,6,7,8,10,12,15,18,21,25,32},
	{10,12,15,18,22,28,35,45,60,80,110},
	{4,5,6,7,8,10,12,14,16,18,22}
};//基础得分，每行一种模式
int bonus_score[] = { 0, 1, 2, 4, 8 };//多消得分
int target_score[3][10] = {
	{50,120,200,300,450,700,1000,1500,2200,3000} ,
	{60,150,300,500,800,1200,2000,3000,5000,7500},
	{60,150,250,400,600,900,1400,2000,2800,4000}
};//目标分数，每行一种模式
int level = 0;//当前关卡
bool level_up = false;
bool down_press = false;//解决快速下落时的不匀速问题

string text = "";
int score_x = 16;//显示分数的位置
int score_y = 9;
int colorboard[] = { 3,10,11,12,13,14 };//调色板
int colornum = sizeof(colorboard)/ sizeof(colorboard[0]);

//道具模式专用
int item_x = 16;
int item_y = 14;
int moju = 0;
int buding = 0;
int baibian = 0;
int no_delete = 0;
bool same = false;//判断下一个方块是否和当前的相同
bool item1_using = false, item2_using = false, item3_using = false;//判断道具是否正在使用
bool get_item = false;//获得道具
int moju_turn = 0;//方块模具剩余轮数
clock_t item_time;//道具提示时间


int random(int x) {
	return rand() % x;
}

int random_y(int width) {//初始方块所在的列不定
	int y = random(width - 4);
	if (y == 0) {
		y = 1;
	}
	return y;
}

void refresh_score() {
	text = "Level " + to_string(level);
	drawText(score_x + 1, score_y, text);
	text = "当前分数：" + to_string(score);
	drawText(score_x, score_y + 3, text);
	if (level <= 9) {
		text = "目标分数：" + to_string(target_score[mode][level]);
	}
	else {
		text = "目标分数：--";
	}
	drawText(score_x, score_y + 2, text);
}

void item_prompt(string text) {
	string clear = "                                         ";
	drawText(score_x + 8, score_y + 3, clear);
	drawText(score_x + 8, score_y + 3, text);
	drawItem(item_x, item_y);
	item_time = clock();//获得道具提示时间
	get_item = true;
}

void moju_effect(Block block, Block* nextBlock) {//方块模具效果
	moju -= 1;
	item1_using = true;
	moju_turn += 2;
	nextBlock->update(0, 0, block.type, 0, block.color);
	drawNext(*nextBlock);
	text = "成功使用方块模具！";
	item_prompt(text);
}

void buding_effect(Block* block) {//补丁效果
	if (item2_using) {
		string text = "你已经对该方块使用过补丁了！";
		item_prompt(text);
		return;
	}
	buding -= 1;
	item2_using = true;
	cleanBlock(*block);
	block->update(block->x, block->y, 7, 0, block->color);
	drawBlock(*block);
	text = "成功使用补丁！";
	item_prompt(text);
}

void baibian_effect() {//补丁效果
	if (item3_using) {
		string text = "你已经对该方块使用过快速思考了！";
		item_prompt(text);
		return;
	}
	baibian -= 1;
	item3_using = true;
	text = "成功使用快速思考！";
	item_prompt(text);
}

int main() {
start:
	mode = -1;
	system("cls");
	scene_title();
	system("cls");

	int height = 24;//窗口高度
	int width = 15;//窗口宽度
	score = 0;
	level = 0;
	moju = 0;
	buding = 0;
	baibian = 0;
	no_delete = 0;

	/* 初始化地图 */
	int** map;
	map = (int**) new int* [height];
	for (int i = 0; i < height; i++) {
		*(map + i) = new int[width];
	}

	drawInit(height, width);
	mapInit(map);//生成可通行和不可通行处
	drawMap(map);//画出对应格子
	drawNext_window();
	refresh_score();

	switch (mode) {
	case 0:
		text = "经典模式"; break;
	case 1:
		text = "天命模式"; break;
	case 2://道具模式专用
		text = "道具模式";
		drawItem(item_x, item_y);
		drawItemIntro(item_x, item_y);
	}
	drawText(-6, 2, text);

	/*产生方块*/
	srand((unsigned)time(NULL));
	int blocktype = random(BLOCKKIND);

	int y = random_y(width);
	int direction = 0;
	if (mode == 1) { direction = random(4); }//天命模式随机取方向
	Block block(2, y, blocktype, direction);
	drawBlock(block);

	/* 下一个方块 */
	blocktype = random(BLOCKKIND);
	if (mode == 1) { direction = random(4); }//天命模式随机取方向
	Block nextBlock(0, 0, blocktype, direction);
	drawNext(nextBlock);
	Cursorpos(0, 25);

	clock_t start, end, level_up_text_time;
	int act = 0;//记录动作

	while (true) {
		start = clock();
		end = clock();
		if (level_up && (clock() - level_up_text_time >= 2500)) {
			text = "         ";
			drawText(score_x + 8, score_y, text);
			level_up = false;
		}
		if (get_item && clock() - item_time >= 2000) {
			text = "                                         ";
			drawText(score_x + 8, score_y + 3, text);
			get_item = false;
		}

		while (end - start <= speed[level]) {//允许操作的时间间隔
			act = action(map, &block, -1);
			switch (act) {
			case 1: down_press = false; break;
			case 2: moju_effect(block, &nextBlock); break;
			case 3: buding_effect(&block); break;
			case 4: baibian_effect(); break;
			}
			end = clock();
			if (act == 1 || down_press) { break; }//如果落到底部或加速下落直接结束本次循环
		}

		if (down_press) { down_press = false; continue; }

		if (action(map, &block, 80) == 1) {//操作时间结束，方块自动下落一格
			int num = clearLine(map, height, width);
			if (num > 0) {
				cleanLine(map);
				score += bonus_score[num] * basic_score[mode][level];
				text = "当前分数：" + to_string(score);
				drawText(score_x, score_y + 3, text);
				if (mode == 2) {
					no_delete = 0;
					text = "获取方式：连续10轮没有消除任何一行。当前还剩" + to_string(10 - no_delete) + "轮   ";
					drawText(item_x, item_y + 6, text);
				}
			}
			if (mode == 2) {
				if (num >= 3) {
					baibian += 1;
					text = "获得快速思考×1！";
					item_prompt(text);
				}
				if (num == 0) {
					no_delete += 1;
					if (no_delete == 10) {
						buding += 1;
						text = "获得补丁×1！";
						item_prompt(text);
						no_delete = 0;
					}
					text = "获取方式：连续10轮没有消除任何一行。当前还剩" + to_string(10 - no_delete) + "轮   ";
					drawText(item_x, item_y + 6, text);
				}
			}
			//读取下一个方块
			int y = random_y(width);
			if (mode == 2) {
				if (same == false) {//连续出现3个相同方块时，第二个和第三个不算
					if (block.type == nextBlock.type && item1_using == false && item3_using == false) {
						same = true;
						moju += 1;
						text = "获得方块模具×1！";
						item_prompt(text);
					}
				}
				else {
					same = false;
				}
			}
			block.update(2, y, nextBlock.type, nextBlock.direction, nextBlock.color);
			blocktype = random(BLOCKKIND);
			if (mode == 2 && blocktype == block.type && (float)random(100) / 100 < 0.8) {
				blocktype = random(BLOCKKIND);//暗改在道具模式中连出两个一样方块的概率（bushi
			}
			if (moju_turn > 0) {
				moju_turn -= 1;
				if (moju_turn == 0) {
					item1_using = false;
				}
			}
			if (moju_turn == 0) {
				int d = 0;
				if (mode == 1) { d = random(4); }
				nextBlock.update(0, 0, blocktype, d, colorboard[rand() % colornum]);
			}
			drawNext(nextBlock);
			drawBlock(block);
			item2_using = false;
			item3_using = false;

			if (ifCrash(map, &block)) {//新方块碰到了已有方块，游戏结束
				Cursorpos(0, 25);
				std::cout << "你挂了。按任意键返回标题画面。" << endl;
				break;
			}
		}

		if (level <= 9 && score >= target_score[mode][level] ) {
			level += 1;
			refresh_score();
			text = "level up!";
			drawText(score_x + 8, score_y, text);
			level_up = true;
			level_up_text_time = clock();
		}
	}
	while (true) {
		if (_kbhit()) {//检查是否按下某键
			_getch();
			mode = -1;
			goto start;
		}
	}
	return 0;

}

