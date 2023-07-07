#pragma once
#include "block.h"
#include "scene.h"
#include <string>
#include <conio.h>

using std::string;


class Game {
private:
	Scene_Map* map;
	Scene_NextWindow* next_window;
	Scene* scene_score;
	Scene_Item* scene_item;

	int wait_in_action();
public:
	Game(Scene_Map* _map, Scene_NextWindow* _next_window, Scene* _scene_score, Scene_Item* _scene_item):
		map(_map), next_window(_next_window), scene_score(_scene_score), scene_item(_scene_item){}
	void refresh_score();
	void new_block();//��һ�����ɷ������һ������
	void next_block();//��ȡ��һ�����鲢�����µ���һ������
	int wait_action(int press_key);//�ȴ�����
	void rotation();//��ת����
	int move(int x, int y, int direction);//��/��/���ƶ�
	void clear_event();//����Ƿ�����
	void use_item(int type);//ʹ�õ���
	void item_prompt(const string& text);//���/ʹ�õ�����ʾ
};