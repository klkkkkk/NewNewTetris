#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include <windows.h>//����̨�����Ҫͷ�ļ�
#include <string>
#include "block.h"
#include "constant.h"
#include "global.h"

using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������

/*0�ޣ�1������2�̣�3ǳ����4�죬5�ϣ�6�ƣ�7�ף�8�ң�9������10���̣�11�࣬12�ۺ죬13���ϣ�14����*/
void SetColor(unsigned short ForeColor = 3, unsigned short BackGroundColor = 0) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //���������Ϊ��
	SetConsoleTextAttribute(hCon, ForeColor | BackGroundColor);
}

//��Ϸ���ڴ�С
int height = 0;
int width = 0;
//��ʾ���ڴ�С
int nextH = 8;
int nextW = 8;

void drawInit(int h, int w) {
	height = h;
	width = w;
}

//���ù��λ��
void Cursorpos(int x, int y) {
	COORD posPoint = { ORIGIN_X + x * 2, ORIGIN_Y + y }; //��������
	SetConsoleCursorPosition(hOut, posPoint);
}

void mapInit(int** map) {//mapָ��һ���е����飬��ÿ���ְ���һ���е����飬�൱�ڶ�ά����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {//���ڱ߽�
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
				cout << "��";	// ǽ�� 
				SetColor(7);
			}
			else {
				cout << "��"; 	// ���ƶ����� 
			}
		}
		cout << endl;
	}
}

void drawBlock(Block block) {//��������
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(y + j, x + i);
			if (block.shapes[block.type][i][j] >= 1 && x + i >= 0 && x + i < height - 1
				&& y + j < width - 1 && y + j > 0) {
				SetColor(block.color);
				std::cout << "��";
				SetColor(7);
			}
		}
	}
	Cursorpos(0, 0);
}

void cleanBlock(Block block) {//�������
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(y + j, x + i);
			if (block.shapes[block.type][i][j] >= 1 && x + i >= 0 && x + i < height - 1
				&& y + j < width - 1 && y + j > 0) {
				std::cout << "��";
			}
		}
	}
	Cursorpos(0, 0);
}

void addBlock(int** map, Block block) {//�����Ѿ����µķ���
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

void cleanLine(int** map) {//�������
	drawMap(map);
	Cursorpos(0, 0);
}

void drawNext_window() {
	for (int i = 0; i < nextH; i++) {
		Cursorpos(width, i);
		for (int j = 0; j < nextW; j++) {
			/*��һȦǽ*/
			if (i == nextH - 1 || i == 0 || j == 0 || j == nextW - 1) {
				std::cout << "��";
			}
			else {
				std::cout << "  ";
			}
		}
	}
	Cursorpos(0, height);
}

void drawNext(Block block) {//��һ�����
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Cursorpos(width + 2 + j, 2 + i);
			if (block.shapes[block.type][i][j] >= 1) {
				SetColor(block.color);
				std::cout << "��";
				SetColor(7);
			}
			else {
				std::cout << "  ";
			}
		}
	}
	Cursorpos(0, 0);
}

void drawText(int x, int y, string text) {//������λ��չʾ�����ı�
	Cursorpos(x, y);
	std::cout << text;
}

void drawItem(int x, int y) {//����ģʽչʾ����
	string text = "����ģ��(Z)  ��" + to_string(moju) + "  ";
	drawText(x, y, text);
	text = "����(X)  ��" + to_string(buding) + "  ";
	drawText(x, y + 4, text);
	text = "����˼��(C)  ��" + to_string(baibian) + "  ";
	drawText(x, y + 8, text);
}
void drawItemIntro(int x, int y) {//���߽���
	string text;
	text = "���ã��������������ɺ͵�ǰ����һ����";
	drawText(x, y + 1, text);
	text = "��ȡ��ʽ�����õ��߸�Ԥ���������������2����ͬ�ķ��顣";
	drawText(x, y + 2, text);
	text = "���ã�����ǰ������һ��С���顣";
	drawText(x, y + 5, text);
	text = "��ȡ��ʽ������10��û�������κ�һ�С���ǰ��ʣ" + to_string(10 - no_delete) + "��";
	drawText(x, y + 6, text);
	text = "���ã���ת��ǰ�����ʹ�������Ϊ��һ����״�ķ��顣";
	drawText(x, y + 9, text);
	text = "��ȡ��ʽ��һ��������3�л����ϡ�";
	drawText(x, y + 10, text);
}