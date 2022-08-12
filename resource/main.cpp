#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>//getch()����
#include <stdlib.h>//system()����
#include <time.h>
#include "block.h"
#include "draw.h"
#include "action.h"
#include "check.h"
#include "constant.h"
using namespace std;

extern void scene_title();

int mode = -1;//��Ϸģʽ
int score = 0;//�÷�
int speed[] = { 750,700,650,600,550,450,400,350,300,250,200 };//���������ٶ�
int basic_score[3][11] = {
	{5,6,7,8,10,12,15,18,21,25,32},
	{10,12,15,18,22,28,35,45,60,80,110},
	{4,5,6,7,8,10,12,14,16,18,22}
};//�����÷֣�ÿ��һ��ģʽ
int bonus_score[] = { 0, 1, 2, 4, 8 };//�����÷�
int target_score[3][10] = {
	{50,120,200,300,450,700,1000,1500,2200,3000} ,
	{60,150,300,500,800,1200,2000,3000,5000,7500},
	{60,150,250,400,600,900,1400,2000,2800,4000}
};//Ŀ�������ÿ��һ��ģʽ
int level = 0;//��ǰ�ؿ�
bool level_up = false;
bool down_press = false;//�����������ʱ�Ĳ���������

string text = "";
int score_x = 16;//��ʾ������λ��
int score_y = 9;
int colorboard[] = { 3,10,11,12,13,14 };//��ɫ��
int colornum = sizeof(colorboard)/ sizeof(colorboard[0]);

//����ģʽר��
int item_x = 16;
int item_y = 14;
int moju = 0;
int buding = 0;
int baibian = 0;
int no_delete = 0;
bool same = false;//�ж���һ�������Ƿ�͵�ǰ����ͬ
bool item1_using = false, item2_using = false, item3_using = false;//�жϵ����Ƿ�����ʹ��
bool get_item = false;//��õ���
int moju_turn = 0;//����ģ��ʣ������
clock_t item_time;//������ʾʱ��


int random(int x) {
	return rand() % x;
}

int random_y(int width) {//��ʼ�������ڵ��в���
	int y = random(width - 4);
	if (y == 0) {
		y = 1;
	}
	return y;
}

void refresh_score() {
	text = "Level " + to_string(level);
	drawText(score_x + 1, score_y, text);
	text = "��ǰ������" + to_string(score);
	drawText(score_x, score_y + 3, text);
	if (level <= 9) {
		text = "Ŀ�������" + to_string(target_score[mode][level]);
	}
	else {
		text = "Ŀ�������--";
	}
	drawText(score_x, score_y + 2, text);
}

void item_prompt(string text) {
	string clear = "                                         ";
	drawText(score_x + 8, score_y + 3, clear);
	drawText(score_x + 8, score_y + 3, text);
	drawItem(item_x, item_y);
	item_time = clock();//��õ�����ʾʱ��
	get_item = true;
}

void moju_effect(Block block, Block* nextBlock) {//����ģ��Ч��
	moju -= 1;
	item1_using = true;
	moju_turn += 2;
	nextBlock->update(0, 0, block.type, 0, block.color);
	drawNext(*nextBlock);
	text = "�ɹ�ʹ�÷���ģ�ߣ�";
	item_prompt(text);
}

void buding_effect(Block* block) {//����Ч��
	if (item2_using) {
		string text = "���Ѿ��Ը÷���ʹ�ù������ˣ�";
		item_prompt(text);
		return;
	}
	buding -= 1;
	item2_using = true;
	cleanBlock(*block);
	block->update(block->x, block->y, 7, 0, block->color);
	drawBlock(*block);
	text = "�ɹ�ʹ�ò�����";
	item_prompt(text);
}

void baibian_effect() {//����Ч��
	if (item3_using) {
		string text = "���Ѿ��Ը÷���ʹ�ù�����˼���ˣ�";
		item_prompt(text);
		return;
	}
	baibian -= 1;
	item3_using = true;
	text = "�ɹ�ʹ�ÿ���˼����";
	item_prompt(text);
}

int main() {
start:
	mode = -1;
	system("cls");
	scene_title();
	system("cls");

	int height = 24;//���ڸ߶�
	int width = 15;//���ڿ��
	score = 0;
	level = 0;
	moju = 0;
	buding = 0;
	baibian = 0;
	no_delete = 0;

	/* ��ʼ����ͼ */
	int** map;
	map = (int**) new int* [height];
	for (int i = 0; i < height; i++) {
		*(map + i) = new int[width];
	}

	drawInit(height, width);
	mapInit(map);//���ɿ�ͨ�кͲ���ͨ�д�
	drawMap(map);//������Ӧ����
	drawNext_window();
	refresh_score();

	switch (mode) {
	case 0:
		text = "����ģʽ"; break;
	case 1:
		text = "����ģʽ"; break;
	case 2://����ģʽר��
		text = "����ģʽ";
		drawItem(item_x, item_y);
		drawItemIntro(item_x, item_y);
	}
	drawText(-6, 2, text);

	/*��������*/
	srand((unsigned)time(NULL));
	int blocktype = random(BLOCKKIND);

	int y = random_y(width);
	int direction = 0;
	if (mode == 1) { direction = random(4); }//����ģʽ���ȡ����
	Block block(2, y, blocktype, direction);
	drawBlock(block);

	/* ��һ������ */
	blocktype = random(BLOCKKIND);
	if (mode == 1) { direction = random(4); }//����ģʽ���ȡ����
	Block nextBlock(0, 0, blocktype, direction);
	drawNext(nextBlock);
	Cursorpos(0, 25);

	clock_t start, end, level_up_text_time;
	int act = 0;//��¼����

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

		while (end - start <= speed[level]) {//���������ʱ����
			act = action(map, &block, -1);
			switch (act) {
			case 1: down_press = false; break;
			case 2: moju_effect(block, &nextBlock); break;
			case 3: buding_effect(&block); break;
			case 4: baibian_effect(); break;
			}
			end = clock();
			if (act == 1 || down_press) { break; }//����䵽�ײ����������ֱ�ӽ�������ѭ��
		}

		if (down_press) { down_press = false; continue; }

		if (action(map, &block, 80) == 1) {//����ʱ������������Զ�����һ��
			int num = clearLine(map, height, width);
			if (num > 0) {
				cleanLine(map);
				score += bonus_score[num] * basic_score[mode][level];
				text = "��ǰ������" + to_string(score);
				drawText(score_x, score_y + 3, text);
				if (mode == 2) {
					no_delete = 0;
					text = "��ȡ��ʽ������10��û�������κ�һ�С���ǰ��ʣ" + to_string(10 - no_delete) + "��   ";
					drawText(item_x, item_y + 6, text);
				}
			}
			if (mode == 2) {
				if (num >= 3) {
					baibian += 1;
					text = "��ÿ���˼����1��";
					item_prompt(text);
				}
				if (num == 0) {
					no_delete += 1;
					if (no_delete == 10) {
						buding += 1;
						text = "��ò�����1��";
						item_prompt(text);
						no_delete = 0;
					}
					text = "��ȡ��ʽ������10��û�������κ�һ�С���ǰ��ʣ" + to_string(10 - no_delete) + "��   ";
					drawText(item_x, item_y + 6, text);
				}
			}
			//��ȡ��һ������
			int y = random_y(width);
			if (mode == 2) {
				if (same == false) {//��������3����ͬ����ʱ���ڶ����͵���������
					if (block.type == nextBlock.type && item1_using == false && item3_using == false) {
						same = true;
						moju += 1;
						text = "��÷���ģ�ߡ�1��";
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
				blocktype = random(BLOCKKIND);//�����ڵ���ģʽ����������һ������ĸ��ʣ�bushi
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

			if (ifCrash(map, &block)) {//�·������������з��飬��Ϸ����
				Cursorpos(0, 25);
				std::cout << "����ˡ�����������ر��⻭�档" << endl;
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
		if (_kbhit()) {//����Ƿ���ĳ��
			_getch();
			mode = -1;
			goto start;
		}
	}
	return 0;

}

