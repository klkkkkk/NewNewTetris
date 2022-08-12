#pragma once
#include <stdio.h>
#include <iostream>
#include "constant.h"
#include "global.h"
enum blockname { O, I, S, Z, L, J, T };

class Block {//������״�ķ���
public:
	//�����Ͻ�Ϊԭ�㷽�������
	int x;//��x��
	int y;//��y��
	int type;//��������
	int direction;//����0��1��2��3�ֱ������ת0��90��180��270��
	int shapes[BLOCKKIND + 1][4][4];//���з���,�������ռ�õ����ռ�Ϊ4��4
	int color;
public:
	Block(int x, int y, int type, int direction = 0) {
		this->x = x;
		this->y = y;
		this->type = type;
		this->direction = direction;
		this->color = colorboard[rand() % colornum];
		Get_shape(type, direction);
	}
	//���÷�������
	void update(int x, int y, int type, int direction, int color) {
		this->x = x;
		this->y = y;
		this->type = type;
		this->direction = direction;
		this->color = color;
		Get_shape(this->type, this->direction);
	}

	void Rotate(int type) {
		int angle;
		switch (type) {
		case I: angle = 2; break;
		case S: angle = 2; break;
		case Z: angle = 2; break;
		default: angle = 1;
		}
		direction = direction + angle > 3 ? 0 : direction + angle;
		Get_shape(this->type, this->direction);
	}
	void Get_shape(int type, int direction) {//������ַ�����״
		for (int i = 0; i < BLOCKKIND + 1; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					shapes[i][j][k] = 0;
		/* ����
		   ���� */
		shapes[O][1][1] = shapes[O][1][2] = shapes[O][2][1] = shapes[O][2][2] = this->color;
		/* �������� */
		if (direction == 0 || direction == 1) {
			shapes[I][1][0] = shapes[I][1][1] = shapes[I][1][2] = shapes[I][1][3] = this->color;
		}
		else {
			shapes[I][0][1] = shapes[I][1][1] = shapes[I][2][1] = shapes[I][3][1] = this->color;
		}
		/*  ����
		  ����*/
		if (direction == 0 || direction == 1) {
			shapes[S][1][1] = shapes[S][1][2] = shapes[S][2][0] = shapes[S][2][1] = this->color;
		}
		else {
			shapes[S][0][0] = shapes[S][1][0] = shapes[S][1][1] = shapes[S][2][1] = this->color;
		}
		/*  ����
			  ����*/
		if (direction == 0 || direction == 1) {
			shapes[Z][1][0] = shapes[Z][1][1] = shapes[Z][2][1] = shapes[Z][2][2] = this->color;
		}
		else {
			shapes[Z][0][1] = shapes[Z][1][1] = shapes[Z][1][0] = shapes[Z][2][0] = this->color;
		}
		/*  ��
			��
			����*/
		switch (direction) {
		case 0: shapes[L][0][1] = shapes[L][1][1] = shapes[L][2][1] = shapes[L][2][2] = this->color; break;
		case 1: shapes[L][1][0] = shapes[L][1][1] = shapes[L][1][2] = shapes[L][2][0] = this->color; break;
		case 2: shapes[L][0][1] = shapes[L][0][2] = shapes[L][1][2] = shapes[L][2][2] = this->color; break;
		case 3: shapes[L][1][2] = shapes[L][2][0] = shapes[L][2][1] = shapes[L][2][2] = this->color; break;
		}
		/*  ��
			��
		  ����*/
		switch (direction) {
		case 0: shapes[J][0][2] = shapes[J][1][2] = shapes[J][2][2] = shapes[J][2][1] = this->color; break;
		case 1: shapes[J][1][0] = shapes[J][2][0] = shapes[J][2][1] = shapes[J][2][2] = this->color; break;
		case 2: shapes[J][0][1] = shapes[J][0][2] = shapes[J][1][1] = shapes[J][2][1] = this->color; break;
		case 3: shapes[J][1][0] = shapes[J][1][1] = shapes[J][1][2] = shapes[J][2][2] = this->color; break;
		}
		/*  ��
		  ������*/
		switch (direction) {
		case 0: shapes[T][1][1] = shapes[T][2][0] = shapes[T][2][1] = shapes[T][2][2] = this->color; break;
		case 1: shapes[T][0][1] = shapes[T][1][1] = shapes[T][2][1] = shapes[T][1][2] = this->color; break;
		case 2: shapes[T][1][0] = shapes[T][1][1] = shapes[T][1][2] = shapes[T][2][1] = this->color; break;
		case 3: shapes[T][1][0] = shapes[T][0][1] = shapes[T][1][1] = shapes[T][2][1] = this->color; break;
		}
		/*��������ģʽר����*/
		shapes[7][1][1] = this->color;
	}


};
