#pragma once
#include <stdio.h>
#include <iostream>
#include "global.h"

class Scene_Map;
class Scene_NextWindow;

class Block {//������״�ķ���
private:
	//�����Ͻ�Ϊԭ�㷽�������
	int x;//��x��
	int y;//��y��
	int type;//��������
	int direction;//����0��1��2��3�ֱ������ת0��90��180��270��
	int color;
public:
	friend class Scene_Map;
	friend class Scene_NextWindow;

	static int shapes[BLOCKKIND + 1][4][4][4];//���з�����״,�������ռ�õ����ռ�Ϊ4��4

	Block();
	Block(int x, int y, int type, int direction = 0);
	Block(Block& other);
	Block operator=(Block& other);
	//���÷�������
	void update_shape(int type, int direction, int color);
	void get_next_block(Block& nextBlock);
	void update_pos(int x, int y);
	void set_pos(int x, int y);
	void rotate();
	int get_type() const;
	int get_direction() const;
	int get_color() const;
	static void set_shape();
};
