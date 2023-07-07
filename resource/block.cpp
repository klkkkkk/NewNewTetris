#include "block.h"

Block::Block() {
	this->x = 0;
	this->y = 0;
	this->type = 0;
	this->direction = 0;
	this->color = colorboard[0];
}

Block::Block(int x, int y, int type, int direction) {
	this->x = x;
	this->y = y;
	this->type = type;
	this->direction = direction;
	this->color = colorboard[rand() % colornum];
}

Block::Block(Block& other) {
	set_pos(other.x, other.y);
	this->type = other.type;
	this->direction = other.direction;
	this->color = other.color;
}

Block Block::operator=(Block& other) {
	set_pos(other.x, other.y);
	this->type = other.type;
	this->direction = other.direction;
	this->color = other.color;
	return *this;
}

//设置方块属性
void Block::update_shape(int type, int direction, int color) {
	this->type = type;
	this->direction = direction;
	this->color = color;
}

void Block::get_next_block(Block& nextBlock) {
	this->type = nextBlock.type;
	this->direction = nextBlock.direction;
	this->color = nextBlock.color;
}

void Block::update_pos(int x, int y) {
	this->x += x;
	this->y += y;
}

void Block::set_pos(int x, int y) {
	this->x = x;
	this->y = y;
}

void Block::rotate() {
	direction = (direction + 1) % 4;
}

int Block::get_type() const {
	return type;
}
int Block::get_direction() const {
	return direction;
}
int Block::get_color() const {
	return color;
}
void Block::set_shape() {//定义各种方块形状
	/* ■■
	   ■■ */
	for (int d = 0; d < 4; d++) {
		shapes[0][d][1][1] = shapes[0][d][1][2] = shapes[0][d][2][1] = shapes[0][d][2][2] = 1;
	}
	/* ■■■■ */
	for (int d = 0; d < 4; d += 2) {
		shapes[1][d][1][0] = shapes[1][d][1][1] = shapes[1][d][1][2] = shapes[1][d][1][3] = 1;
		shapes[1][d + 1][0][1] = shapes[1][d + 1][1][1] = shapes[1][d + 1][2][1] = shapes[1][d + 1][3][1] = 1;
	}
	/*  ■■
	  ■■*/
	for (int d = 0; d < 4; d += 2) {
		shapes[2][d][1][1] = shapes[2][d][1][2] = shapes[2][d][2][0] = shapes[2][d][2][1] = 1;
		shapes[2][d + 1][0][0] = shapes[2][d + 1][1][0] = shapes[2][d + 1][1][1] = shapes[2][d + 1][2][1] = 1;
	}
	/*  ■■
		  ■■*/
	for (int d = 0; d < 4; d += 2) {
		shapes[3][d][1][0] = shapes[3][d][1][1] = shapes[3][d][2][1] = shapes[3][d][2][2] = 1;
		shapes[3][d + 1][0][1] = shapes[3][d + 1][1][1] = shapes[3][d + 1][1][0] = shapes[3][d + 1][2][0] = 1;
	}
	/*  ■
		■
		■■*/
	shapes[4][0][0][1] = shapes[4][0][1][1] = shapes[4][0][2][1] = shapes[4][0][2][2] = 1;
	shapes[4][1][1][0] = shapes[4][1][1][1] = shapes[4][1][1][2] = shapes[4][1][2][0] = 1;
	shapes[4][2][0][1] = shapes[4][2][0][2] = shapes[4][2][1][2] = shapes[4][2][2][2] = 1;
	shapes[4][3][1][2] = shapes[4][3][2][0] = shapes[4][3][2][1] = shapes[4][3][2][2] = 1;
	/*  ■
		■
	  ■■*/
	shapes[5][0][0][2] = shapes[5][0][1][2] = shapes[5][0][2][2] = shapes[5][0][2][1] = 1;
	shapes[5][1][1][0] = shapes[5][1][2][0] = shapes[5][1][2][1] = shapes[5][1][2][2] = 1;
	shapes[5][2][0][1] = shapes[5][2][0][2] = shapes[5][2][1][1] = shapes[5][2][2][1] = 1;
	shapes[5][3][1][0] = shapes[5][3][1][1] = shapes[5][3][1][2] = shapes[5][3][2][2] = 1;
	/*  ■
	  ■■■*/
	shapes[6][0][1][1] = shapes[6][0][2][0] = shapes[6][0][2][1] = shapes[6][0][2][2] = 1;
	shapes[6][1][0][1] = shapes[6][1][1][1] = shapes[6][1][2][1] = shapes[6][1][1][2] = 1;
	shapes[6][2][1][0] = shapes[6][2][1][1] = shapes[6][2][1][2] = shapes[6][2][2][1] = 1;
	shapes[6][3][1][0] = shapes[6][3][0][1] = shapes[6][3][1][1] = shapes[6][3][2][1] = 1;
	/*■（道具模式专属）*/
	for (int d = 0; d < 4; d++) {
		shapes[7][d][1][1] = 1;
	}
}