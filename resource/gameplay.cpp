#include "gameplay.h"
#include "global.h"
#include "scene.h"
#include <time.h>

using std::string;
using std::to_string;

int random(int x) {
	return rand() % x;
}

int random_y(int width) {//初始方块所在的列不定
	int y = random(width - 4);
	if (y == 0) {
		y = 1;
	}
	return y;
}

void Game::new_block() {
	srand((unsigned)time(NULL));
	int blocktype = random(BLOCKKIND);

	int y = random_y(map->map[0].size());
	int direction = 0;
	if (mode == 1) { direction = random(4); }//天命模式随机取方向
	Block block(2, y, blocktype, direction);
	map->block = block;

	blocktype = random(BLOCKKIND);
	if (mode == 1) { direction = random(4); }//天命模式随机取方向
	next_window->block.update_shape(blocktype, direction, next_window->block.get_color());
}

void Game::next_block() {
	int y = random_y(map->map[0].size());
	map->block.get_next_block(next_window->block);
	map->block.set_pos(2, y);
	if (!scene_item->all_item[ITEM_1]->is_using()) {
		int blocktype = random(BLOCKKIND);
		if (mode == 2 && blocktype == map->block.get_type() && (float)random(100) / 100 < 0.8) {
			blocktype = random(BLOCKKIND);//暗改在道具模式中连出两个一样方块的概率（bushi
		}
		int d = 0;
		if (mode == 1) { d = random(4); }
		next_window->block.update_shape(blocktype, d, colorboard[rand() % colornum]);
	}
}

void Game::item_prompt(const string& text) {
	string clear = "                                         ";
	scene_score->set_cursor(8, 3);
	scene_score->draw_text(clear);
	scene_score->set_cursor(8, 3);
	scene_score->draw_text(text);
	item_time = clock();//获得道具提示时间
	get_item = true;
}

void Game::use_item(int type){
	if (mode != 2) {
		return;
	}
	switch (type) {
	case ITEM_1://方块模具
		if (scene_item->all_item[ITEM_1]->use()) {
			next_window->block.get_next_block(map->block);
			next_window->draw_block();
			string text = "成功使用" + scene_item->all_item[ITEM_1]->name + "！";
			item_prompt(text);
			scene_item->refresh(ITEM_1);
		}
		break;
	case ITEM_2://补丁
		if (scene_item->all_item[ITEM_2]->is_using()) {
			string text = "你已经对该方块使用过" + scene_item->all_item[ITEM_2]->name + "了！";
			item_prompt(text);
		}
		if (scene_item->all_item[ITEM_2]->use()) {
			map->clear_block();
			map->block.update_shape(7, 0, map->block.get_color());
			map->draw_block();
			string text = "成功使用" + scene_item->all_item[ITEM_2]->name + "！";
			item_prompt(text);
			scene_item->refresh(ITEM_2);
		}
		break;
	case ITEM_3://快速思考
		if (scene_item->all_item[ITEM_3]->is_using()) {
			string text = "你已经对该方块使用过" + scene_item->all_item[ITEM_3]->name + "了！";
			item_prompt(text);
		}
		if (scene_item->all_item[ITEM_3]->use()) {
			string text = "成功使用" + scene_item->all_item[ITEM_3]->name + "！";
			scene_item->refresh(ITEM_3);
			item_prompt(text);
		}
		break;
	}
}

void Game::clear_event() {
	int num = map->clear_line();
	string text;
	if (mode == 2) {
		if (scene_item->all_item[ITEM_2]->check_get(num)) {
			text = "获得"+ scene_item->all_item[ITEM_2]->name +"×1！";
			item_prompt(text);
		}
		scene_item->refresh(ITEM_2);
		if (scene_item->all_item[ITEM_3]->check_get(num)) {
			text = "获得" + scene_item->all_item[ITEM_3]->name + "×1！";
			item_prompt(text);
			scene_item->refresh(ITEM_3);
		}
	}
	if (num > 0) {
		map->draw_map();
		scene_score->set_cursor(0, 3);
		score += bonus_score[num] * basic_score[mode][level];
		if (level <= 9 && score >= target_score[mode][level]) {
			level += 1;
			text = "level up!";
			scene_score->set_cursor(8, 0);
			scene_score->draw_text(text);
			level_up = true;
		}
		refresh_score();
	}
}

void Game::refresh_score(){
	string text = "Level " + to_string(level);
	scene_score->set_cursor(1, 0);
	scene_score->draw_text(text);
	text = "当前分数：" + to_string(score);
	scene_score->set_cursor(0, 3);
	scene_score->draw_text(text);
	if (level <= 9) {
		text = "目标分数：" + to_string(target_score[mode][level]);
	}
	else {
		text = "目标分数：--";
	}
	scene_score->set_cursor(0, 2);
	scene_score->draw_text(text);
}

int Game::wait_action(int press_key){
	int bottom = 0;//标志是否到达底部
	int key = press_key;
	if (key == -1) {//等待操作，减少检查次数
		key = wait_in_action();
	}
	switch (key) {
	case 72://上
		if (mode != 1) {
			if (scene_item->all_item[ITEM_3]->is_using()) {
				map->clear_block();
				map->block.update_shape(rand() % BLOCKKIND, rand() % 4, map->block.get_color());
				map->draw_block();
			}
			else {
				rotation();
			}
		}
		break;
	case 80: bottom = move(1, 0, 1); break; //下
	case 75: move(0, -1, 0); break;//左
	case 77: move(0, 1, 0); break;//右
	case ITEM_1_SHORTCUT: return ITEM_1;//方块模具
	case ITEM_2_SHORTCUT: return ITEM_2;//补丁
	case ITEM_3_SHORTCUT: return ITEM_3;//百变方块
	}
	if (bottom == 1) {//到达底部，进行额外判定
		return BOTTOM;
	}
	return -1;
}

int Game::wait_in_action() {//等待操作
	clock_t start, now;
	start = clock();
	int key = -1;

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
		if (pass_time >= 50) {
			break;
		}
	}
	return key;
}

void Game::rotation(){
	Block oldblock(map->block);
	map->clear_block();	 // 擦除旋转前的方块 
	map->block.rotate();
	if (map->crash()) {//发现碰撞,回到原先状态
		map->block = oldblock;
	}
	map->draw_block();
}

int Game::move(int x, int y, int direction) {
	map->clear_block();
	map->block.update_pos(x, y);
	if (map->crash()) {//发现碰撞，移动取消
		map->block.update_pos(-x, -y);
		map->draw_block();
		if (direction == 1) {//落到了底部，生成固定方块
			map->place_block();
		}
		return 1;//用于下落产生的额外判定
	}
	map->draw_block();
	return 0;
}