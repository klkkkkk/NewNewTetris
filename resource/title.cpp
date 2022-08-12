#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <windows.h>//控制台编程主要头文件
#include "constant.h"
#include "global.h"

namespace title {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
	void Cursorpos(int x, int y) {
		COORD posPoint = { x * 2, y }; //设置坐标
		SetConsoleCursorPosition(hOut, posPoint);
	}
}
using namespace title;

int N[5][5] = {
	{1,0,0,0,1},
	{1,1,0,0,1},
	{1,0,1,0,1},
	{1,0,0,1,1},
	{1,0,0,0,1} };
int E[5][5] = {
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,1,1,1,1} };
int W[5][5] = {
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{1,0,1,0,1},
	{0,1,0,1,0}
};
int T[5][5] = {
	{1,1,1,1,1},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0}
};
int R[5][5] = {
	{1,1,1,1,0},
	{1,0,0,0,1},
	{1,1,1,1,0},
	{1,0,0,1,0},
	{1,0,0,0,1}
};
int I[5][5] = {
	{0,1,1,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,1,1,1,0},
};
int S[5][5] = {
	{1,1,1,1,1},
	{1,0,0,0,0},
	{1,1,1,1,1},
	{0,0,0,0,1},
	{1,1,1,1,1},
};
int ox = 10, oy = 2;//原点坐标，左上角为原点
struct coord {
	int x;
	int y;
};
void draw_cursor(coord cursor) {
	Cursorpos(cursor.x, cursor.y);
	std::cout << "→";
}
void delete_cursor(coord cursor) {
	Cursorpos(cursor.x, cursor.y);
	std::cout << "  ";
}
void delete_text(int x, int y) {
	Cursorpos(x, y);
	for (int i = 0; i < 8; i++) {
		std::cout << "                                                                               " << std::endl;
	}
}

coord draw_letter(int letter[5][5], coord c) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Cursorpos(c.x + j, c.y + i);
			if (letter[i][j] == 1) {
				std::cout << "■";
			}
		}
	}
	c.x += 6;
	return c;
}

void scene_title() {
	coord pos;
	coord cursor;
	cursor.x = ox + 4;
	cursor.y = oy + 14;
	int key = -1;//按键
	int curmode = 0;
	pos.x = ox;
	pos.y = oy;
	pos = draw_letter(N, pos);
	pos = draw_letter(E, pos);
	pos = draw_letter(W, pos);
	pos.x += 3;
	pos = draw_letter(N, pos);
	pos = draw_letter(E, pos);
	pos = draw_letter(W, pos);
	pos.x = ox + 1;
	pos.y = oy + 6;
	pos = draw_letter(T, pos);
	pos = draw_letter(E, pos);
	pos = draw_letter(T, pos);
	pos = draw_letter(R, pos);
	pos = draw_letter(I, pos);
	pos = draw_letter(S, pos);
	pos.x = ox + 4;
	pos.y = oy + 14;
	draw_cursor(cursor);
	std::cout << "经典模式";
	pos.x += 8;
	Cursorpos(pos.x, pos.y);
	std::cout << "  天命模式";
	pos.x += 8;
	Cursorpos(pos.x, pos.y);
	std::cout << "  道具模式";
	pos.x += 8;
	Cursorpos(pos.x, pos.y);
	std::cout << "  操作说明";
	Cursorpos(ox + 12, oy + 12);
	std::cout << "左右键选择游戏模式，空格键确认";
	Cursorpos(ox, oy + 17);
	//初始化显示经典模式说明
	std::cout << "经典的俄罗斯方块规则，消除尽可能多的行来获取高分。";
	Cursorpos(ox, oy + 19);
	std::cout << "每达到一个目标分即可进入下一关，同时方块下落速度也会变快！";
	Cursorpos(0, 0);
	while (true) {
		if (_kbhit()) {//检查是否按下某键
			key = _getch();//获取按下键的ascii码
			switch (key) {
			case 75:
				delete_cursor(cursor);
				if (curmode == 0) {
					curmode = 3;
				}
				else {
					curmode -= 1;
				}
				break;//左
			case 77:
				delete_cursor(cursor);
				if (curmode == 3) {
					curmode = 0;
				}
				else {
					curmode += 1;
				}
				break;//右
			case 32: if (curmode != 3) { mode = curmode; } break;//空格确认
			}
			if (mode >= 0) {
				return;
			}
			if (key != 75 && key != 77) { continue; }
			cursor.x = ox + 4 + curmode * 8;
			cursor.y = oy + 14;
			draw_cursor(cursor);
			delete_text(0, oy + 17);
			Cursorpos(ox, oy + 17);
			switch (curmode) {
			case 0: {//经典模式
				std::cout << "经典的俄罗斯方块规则，消除尽可能多的行来获取高分。";
				Cursorpos(ox, oy + 19);
				std::cout << "每达到一个目标分即可进入下一关，同时方块下落速度也会变快！";
				break;
			}
			case 1: {//天命模式
				std::cout << "在该模式中，你不能旋转方块！但当你填满一行时，";
				Cursorpos(ox, oy + 18);
				std::cout << "你可以额外消去其下面的一行！";
				Cursorpos(ox, oy + 20);
				std::cout << "注意：每个方块都会以随机的朝向出现。";
				break;
			}
			case 2: {//道具模式
				std::cout << "在游戏过程中达成指定条件你将会获得各种不同的道具！";
				Cursorpos(ox, oy + 19);
				std::cout << "运用这些有趣的道具更上一层楼吧！";
				break;
			}
			case 3: {//操作说明
				std::cout << "↑：旋转方块  ↓：加速方块下落  ←→：左右移动方块";
				Cursorpos(ox, oy + 19);
				std::cout << "Z、X、C：使用道具（仅在道具模式下可用）";
				Cursorpos(ox, oy + 21);
				std::cout << "鼠标点击画面任意位置可暂停";
				break;
			}
			}
			key = -1;
			Cursorpos(0, 0);
		}
	}
}
