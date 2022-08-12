#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "block.h"
#include "global.h"

/* draw */
extern void cleanBlock(Block block);
extern void drawBlock(Block block);
extern void addBlock(int** map, Block block);
/* check */
extern int ifCrash(int** map, Block* block);

int key = 0;//按键
int wait_time = 50;//等待时间

void waitAction() {//等待操作
	clock_t start, now;
	start = clock();

	while (true) {
		if (_kbhit()) {//检查是否按下某键
			key = _getch();//获取按下键的ascii码
			if (key == 80) {//按下下键
				down_press = true;
			}
			break;
		}
		now = clock();
		int pass_time = (double)(now - start);
		if (pass_time >= wait_time) {
			break;
		}
	}
}

int move(int** map, Block* block, int x, int y, int direction) {//direction为0时代表左右移动，1为向下移动
	cleanBlock(*block);
	block->x += x;
	block->y += y;
	if (ifCrash(map, block)) {//发现碰撞，移动取消
		block->x -= x;
		block->y -= y;
		drawBlock(*block);
		if (direction == 1) {//落到了底部，生成固定方块
			addBlock(map, *block);
		}
		return 1;//用于下落产生的额外判定
	}
	drawBlock(*block);
	return 0;

}

void rotation(int** map, Block* block) {
	Block oldblock(block->x, block->y, block->type, block->direction);
	oldblock.color = block->color;
	cleanBlock(*block);	 // 擦除旋转前的方块 
	block->Rotate(block->type);
	if (ifCrash(map, block)) {//发现碰撞,回到原先状态
		block->update(block->x, block->y, oldblock.type, oldblock.direction, oldblock.color);
	}
	drawBlock(*block);
}

int action(int** map, Block* block, int press_key) {//操作的具体实现
	int buttom = 0;//标志是否到达底部
	key = press_key;
	if (key == -1) {//等待操作
		waitAction();
	}
	switch (key) {
	case 72:
		if (mode != 1) {
			if (item3_using) {
				cleanBlock(*block);
				block->update(block->x, block->y, rand() % BLOCKKIND, rand() % 4, block->color);
				drawBlock(*block);
			}
			else {
				rotation(map, block);
			}
		}
		break;//上
	case 80: buttom = move(map, block, 1, 0, 1); break; //下
	case 75: move(map, block, 0, -1, 0); break;//左
	case 77: move(map, block, 0, 1, 0); break;//右
	case 'z': if (mode == 2 && moju > 0) { return 2; } break;//方块模具
	case 'x': if (mode == 2 && buding > 0) { return 3; } break;//补丁
	case 'c': if (mode == 2 && baibian > 0) { return 4; } break;//百变方块
	}
	if (buttom == 1) {//到达底部，进行额外判定
		return 1;
	}
	return 0;
}
