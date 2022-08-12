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

int key = 0;//����
int wait_time = 50;//�ȴ�ʱ��

void waitAction() {//�ȴ�����
	clock_t start, now;
	start = clock();

	while (true) {
		if (_kbhit()) {//����Ƿ���ĳ��
			key = _getch();//��ȡ���¼���ascii��
			if (key == 80) {//�����¼�
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

int move(int** map, Block* block, int x, int y, int direction) {//directionΪ0ʱ���������ƶ���1Ϊ�����ƶ�
	cleanBlock(*block);
	block->x += x;
	block->y += y;
	if (ifCrash(map, block)) {//������ײ���ƶ�ȡ��
		block->x -= x;
		block->y -= y;
		drawBlock(*block);
		if (direction == 1) {//�䵽�˵ײ������ɹ̶�����
			addBlock(map, *block);
		}
		return 1;//������������Ķ����ж�
	}
	drawBlock(*block);
	return 0;

}

void rotation(int** map, Block* block) {
	Block oldblock(block->x, block->y, block->type, block->direction);
	oldblock.color = block->color;
	cleanBlock(*block);	 // ������תǰ�ķ��� 
	block->Rotate(block->type);
	if (ifCrash(map, block)) {//������ײ,�ص�ԭ��״̬
		block->update(block->x, block->y, oldblock.type, oldblock.direction, oldblock.color);
	}
	drawBlock(*block);
}

int action(int** map, Block* block, int press_key) {//�����ľ���ʵ��
	int buttom = 0;//��־�Ƿ񵽴�ײ�
	key = press_key;
	if (key == -1) {//�ȴ�����
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
		break;//��
	case 80: buttom = move(map, block, 1, 0, 1); break; //��
	case 75: move(map, block, 0, -1, 0); break;//��
	case 77: move(map, block, 0, 1, 0); break;//��
	case 'z': if (mode == 2 && moju > 0) { return 2; } break;//����ģ��
	case 'x': if (mode == 2 && buding > 0) { return 3; } break;//����
	case 'c': if (mode == 2 && baibian > 0) { return 4; } break;//�ٱ䷽��
	}
	if (buttom == 1) {//����ײ������ж����ж�
		return 1;
	}
	return 0;
}
