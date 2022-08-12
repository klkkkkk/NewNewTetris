#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include <windows.h>//控制台编程主要头文件
#include <string>
#include "block.h"
#include "constant.h"
#include "global.h"

using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄

/*0无，1深蓝，2绿，3浅蓝，4红，5紫，6黄，7白，8灰，9天蓝，10亮绿，11青，12粉红，13真紫，14淡黄*/
void SetColor(unsigned short ForeColor = 3, unsigned short BackGroundColor = 0) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //本例以输出为例
	SetConsoleTextAttribute(hCon, ForeColor | BackGroundColor);
}

//游戏窗口大小
int height = 0;
int width = 0;
//提示窗口大小
int nextH = 8;
int nextW = 8;

void drawInit(int h, int w) {
	height = h;
	width = w;
}

//设置光标位置
void Cursorpos(int x, int y) {
	COORD posPoint = { ORIGIN_X + x * 2, ORIGIN_Y + y }; //设置坐标
	SetConsoleCursorPosition(hOut, posPoint);
}

void mapInit(int** map) {//map指向一个行的数组，而每行又包含一个列的数组，相当于二维数组
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {//窗口边界
				map[i][j] = 1;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
}

void drawMap(int** map) {
	for (int i = 0; i < height; i++) {
		Cursorpos(0, i);
		for (int j = 0; j < width; j++) {
			if (map[i][j] >= 1) {
				if (map[i][j] > 1) {
					SetColor(map[i][j]);
				}
				cout << "■";	// 墙体 
				SetColor(7);
			}
			else {
				cout << "□"; 	// 可移动区域 
			}
		}
		cout << endl;
	}
}

void drawBlock(Block block) {//画出方块
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(y + j, x + i);
			if (block.shapes[block.type][i][j] >= 1 && x + i >= 0 && x + i < height - 1
				&& y + j < width - 1 && y + j > 0) {
				SetColor(block.color);
				std::cout << "■";
				SetColor(7);
			}
		}
	}
	Cursorpos(0, 0);
}

void cleanBlock(Block block) {//清除方块
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(y + j, x + i);
			if (block.shapes[block.type][i][j] >= 1 && x + i >= 0 && x + i < height - 1
				&& y + j < width - 1 && y + j > 0) {
				std::cout << "□";
			}
		}
	}
	Cursorpos(0, 0);
}

void addBlock(int** map, Block block) {//生成已经落下的方块
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block.shapes[block.type][i][j] >= 1 && x + i >= 0 && x + i < height - 1
				&& y + j < width - 1 && y + j > 0) {
				map[x + i][y + j] = block.shapes[block.type][i][j];
			}
		}
	}
}

void cleanLine(int** map) {//清除满行
	drawMap(map);
	Cursorpos(0, 0);
}

void drawNext_window() {
	for (int i = 0; i < nextH; i++) {
		Cursorpos(width, i);
		for (int j = 0; j < nextW; j++) {
			/*画一圈墙*/
			if (i == nextH - 1 || i == 0 || j == 0 || j == nextW - 1) {
				std::cout << "■";
			}
			else {
				std::cout << "  ";
			}
		}
	}
	Cursorpos(0, height);
}

void drawNext(Block block) {//下一块面板
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(width + 2 + j, 2 + i);
			if (block.shapes[block.type][i][j] >= 1) {
				SetColor(block.color);
				std::cout << "■";
				SetColor(7);
			}
			else {
				std::cout << "  ";
			}
		}
	}
	Cursorpos(0, 0);
}

void drawText(int x, int y, string text) {//在任意位置展示任意文本
	Cursorpos(x, y);
	std::cout << text;
}

void drawItem(int x, int y) {//道具模式展示道具
	string text = "方块模具(Z)  ×" + to_string(moju) + "  ";
	drawText(x, y, text);
	text = "补丁(X)  ×" + to_string(buding) + "  ";
	drawText(x, y + 4, text);
	text = "快速思考(C)  ×" + to_string(baibian) + "  ";
	drawText(x, y + 8, text);
}
void drawItemIntro(int x, int y) {//道具介绍
	string text;
	text = "作用：将下两个方块变成和当前方块一样。";
	drawText(x, y + 1, text);
	text = "获取方式：不用道具干预的情况下连续出现2个相同的方块。";
	drawText(x, y + 2, text);
	text = "作用：将当前方块变成一个小方块。";
	drawText(x, y + 5, text);
	text = "获取方式：连续10轮没有消除任何一行。当前还剩" + to_string(10 - no_delete) + "轮";
	drawText(x, y + 6, text);
	text = "作用：旋转当前方块会使其随机变为另一种形状的方块。";
	drawText(x, y + 9, text);
	text = "获取方式：一次性消除3行或以上。";
	drawText(x, y + 10, text);
}