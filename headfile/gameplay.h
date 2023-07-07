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
	void new_block();//第一次生成方块和下一个方块
	void next_block();//获取下一个方块并生成新的下一个方块
	int wait_action(int press_key);//等待操作
	void rotation();//旋转操作
	int move(int x, int y, int direction);//左/右/下移动
	void clear_event();//检查是否消除
	void use_item(int type);//使用道具
	void item_prompt(const string& text);//获得/使用道具提示
};