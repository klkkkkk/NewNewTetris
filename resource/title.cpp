#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <windows.h>//控制台编程主要头文件
#include "global.h"
#include "scene.h"

using std::cout;
using std::endl;
namespace letter {
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
}

void delete_text(Scene_Title& title) {
	title.set_cursor(0, 17);
	for (int i = 0; i < 8; i++) {
		title.draw_text("                                                                               ");
		title.move_cursor(0, 1);
	}
}

void draw_letter(int letter[5][5], Scene_Title& title) {
	title.move_cursor(0, 0);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (letter[i][j] == 1) {
				title.draw_text("■");
			}
			else {
				title.draw_text("  ");
			}
		}
		title.move_cursor(0,1);
	}
	title.move_cursor(6, -5);
}

void scene_title() {
	using namespace letter;
	Scene_Title title(TITLE_OX, TITLE_OY, TITLE_HEIGHT, TITLE_WIDTH);
	int key = -1;//按键
	int curmode = 0;
	draw_letter(N, title);
	draw_letter(E, title);
	draw_letter(W, title);
	title.move_cursor(3, 0);
	draw_letter(N, title);
	draw_letter(E, title);
	draw_letter(W, title);
	title.set_cursor(1, 6);
	draw_letter(T, title);
	draw_letter(E, title);
	draw_letter(T, title);
	draw_letter(R, title);
	draw_letter(I, title);
	draw_letter(S, title);
	title.draw_arrow();
	title.set_cursor(TITLE_CURSOR_X + 1, TITLE_CURSOR_Y);
	title.draw_text("经典模式");
	title.move_cursor(8, 0);
	title.draw_text("天命模式");
	title.move_cursor(8, 0);
	title.draw_text("道具模式");
	title.move_cursor(8, 0);
	title.draw_text("操作说明");
	title.set_cursor(12, 12);
	title.draw_text("左右键选择游戏模式，空格键确认");
	title.set_cursor(0, 17);
	//初始化显示经典模式说明
	title.draw_text("经典的俄罗斯方块规则，消除尽可能多的行来获取高分。");
	title.set_cursor(0, 19);
	title.draw_text("每达到一个目标分即可进入下一关，同时方块下落速度也会变快！");
	title.set_cursor(0,0);
	while (true) {
		if (_kbhit()) {//检查是否按下某键
			key = _getch();//获取按下键的ascii码
			switch (key) {
			case 75://左
				title.delete_arrow();
				curmode = curmode == 0 ? 3 : curmode - 1;
				break;
			case 77://右
				title.delete_arrow();
				curmode = curmode == 3 ? 0 : curmode + 1;
				break;
			case 32: if (curmode != 3) { mode = curmode; } break;//空格确认
			}
			if (mode >= 0) {
				return;
			}
			if (key != 75 && key != 77) { continue; }
			title.set_arrow(TITLE_CURSOR_X + curmode * 8, TITLE_CURSOR_Y);
			title.draw_arrow();
			delete_text(title);
			title.set_cursor(0, 17);
			switch (curmode) {
			case 0: {//经典模式
				title.draw_text("经典的俄罗斯方块规则，消除尽可能多的行来获取高分。");
				title.set_cursor(0, 19);
				title.draw_text("每达到一个目标分即可进入下一关，同时方块下落速度也会变快！");
				break;
			}
			case 1: {//天命模式
				title.draw_text("在该模式中，你不能旋转方块！但当你填满一行时，");
				title.set_cursor(0, 18);
				title.draw_text("你可以额外消去其下面的一行！");
				title.set_cursor(0, 20);
				title.draw_text("注意：每个方块都会以随机的朝向出现。");
				break;
			}
			case 2: {//道具模式
				title.draw_text("在游戏过程中达成指定条件你将会获得各种不同的道具！");
				title.set_cursor(0, 19);
				title.draw_text("运用这些有趣的道具更上一层楼吧！");
				break;
			}
			case 3: {//操作说明
				title.draw_text("↑：旋转方块  ↓：加速方块下落  ←→：左右移动方块");
				title.set_cursor(0, 19);
				title.draw_text("Z、X、C：使用道具（仅在道具模式下可用）");
				title.set_cursor(0, 21);
				title.draw_text("鼠标点击画面任意位置可暂停");
				break;
			}
			}
			key = -1;
			title.set_cursor(0,0);
		}
	}
}
