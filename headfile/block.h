#pragma once
#include <stdio.h>
#include <iostream>
#include "global.h"

class Scene_Map;
class Scene_NextWindow;

class Block {//各种形状的方块
private:
	//以左上角为原点方块的坐标
	int x;//第x行
	int y;//第y列
	int type;//方块类型
	int direction;//朝向，0，1，2，3分别代表旋转0，90，180，270度
	int color;
public:
	friend class Scene_Map;
	friend class Scene_NextWindow;

	static int shapes[BLOCKKIND + 1][4][4][4];//所有方块形状,方块可能占用的最大空间为4×4

	Block();
	Block(int x, int y, int type, int direction = 0);
	Block(Block& other);
	Block operator=(Block& other);
	//设置方块属性
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
