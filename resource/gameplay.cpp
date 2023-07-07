#include "gameplay.h"
#include "global.h"
#include "scene.h"
#include <time.h>

using std::string;
using std::to_string;

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

void Game::new_block() {
	srand((unsigned)time(NULL));
	int blocktype = random(BLOCKKIND);

	int y = random_y(map->map[0].size());
	int direction = 0;
	if (mode == 1) { direction = random(4); }//����ģʽ���ȡ����
	Block block(2, y, blocktype, direction);
	map->block = block;

	blocktype = random(BLOCKKIND);
	if (mode == 1) { direction = random(4); }//����ģʽ���ȡ����
	next_window->block.update_shape(blocktype, direction, next_window->block.get_color());
}

void Game::next_block() {
	int y = random_y(map->map[0].size());
	map->block.get_next_block(next_window->block);
	map->block.set_pos(2, y);
	if (!scene_item->all_item[ITEM_1]->is_using()) {
		int blocktype = random(BLOCKKIND);
		if (mode == 2 && blocktype == map->block.get_type() && (float)random(100) / 100 < 0.8) {
			blocktype = random(BLOCKKIND);//�����ڵ���ģʽ����������һ������ĸ��ʣ�bushi
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
	item_time = clock();//��õ�����ʾʱ��
	get_item = true;
}

void Game::use_item(int type){
	if (mode != 2) {
		return;
	}
	switch (type) {
	case ITEM_1://����ģ��
		if (scene_item->all_item[ITEM_1]->use()) {
			next_window->block.get_next_block(map->block);
			next_window->draw_block();
			string text = "�ɹ�ʹ��" + scene_item->all_item[ITEM_1]->name + "��";
			item_prompt(text);
			scene_item->refresh(ITEM_1);
		}
		break;
	case ITEM_2://����
		if (scene_item->all_item[ITEM_2]->is_using()) {
			string text = "���Ѿ��Ը÷���ʹ�ù�" + scene_item->all_item[ITEM_2]->name + "�ˣ�";
			item_prompt(text);
		}
		if (scene_item->all_item[ITEM_2]->use()) {
			map->clear_block();
			map->block.update_shape(7, 0, map->block.get_color());
			map->draw_block();
			string text = "�ɹ�ʹ��" + scene_item->all_item[ITEM_2]->name + "��";
			item_prompt(text);
			scene_item->refresh(ITEM_2);
		}
		break;
	case ITEM_3://����˼��
		if (scene_item->all_item[ITEM_3]->is_using()) {
			string text = "���Ѿ��Ը÷���ʹ�ù�" + scene_item->all_item[ITEM_3]->name + "�ˣ�";
			item_prompt(text);
		}
		if (scene_item->all_item[ITEM_3]->use()) {
			string text = "�ɹ�ʹ��" + scene_item->all_item[ITEM_3]->name + "��";
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
			text = "���"+ scene_item->all_item[ITEM_2]->name +"��1��";
			item_prompt(text);
		}
		scene_item->refresh(ITEM_2);
		if (scene_item->all_item[ITEM_3]->check_get(num)) {
			text = "���" + scene_item->all_item[ITEM_3]->name + "��1��";
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
	text = "��ǰ������" + to_string(score);
	scene_score->set_cursor(0, 3);
	scene_score->draw_text(text);
	if (level <= 9) {
		text = "Ŀ�������" + to_string(target_score[mode][level]);
	}
	else {
		text = "Ŀ�������--";
	}
	scene_score->set_cursor(0, 2);
	scene_score->draw_text(text);
}

int Game::wait_action(int press_key){
	int bottom = 0;//��־�Ƿ񵽴�ײ�
	int key = press_key;
	if (key == -1) {//�ȴ����������ټ�����
		key = wait_in_action();
	}
	switch (key) {
	case 72://��
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
	case 80: bottom = move(1, 0, 1); break; //��
	case 75: move(0, -1, 0); break;//��
	case 77: move(0, 1, 0); break;//��
	case ITEM_1_SHORTCUT: return ITEM_1;//����ģ��
	case ITEM_2_SHORTCUT: return ITEM_2;//����
	case ITEM_3_SHORTCUT: return ITEM_3;//�ٱ䷽��
	}
	if (bottom == 1) {//����ײ������ж����ж�
		return BOTTOM;
	}
	return -1;
}

int Game::wait_in_action() {//�ȴ�����
	clock_t start, now;
	start = clock();
	int key = -1;

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
		if (pass_time >= 50) {
			break;
		}
	}
	return key;
}

void Game::rotation(){
	Block oldblock(map->block);
	map->clear_block();	 // ������תǰ�ķ��� 
	map->block.rotate();
	if (map->crash()) {//������ײ,�ص�ԭ��״̬
		map->block = oldblock;
	}
	map->draw_block();
}

int Game::move(int x, int y, int direction) {
	map->clear_block();
	map->block.update_pos(x, y);
	if (map->crash()) {//������ײ���ƶ�ȡ��
		map->block.update_pos(-x, -y);
		map->draw_block();
		if (direction == 1) {//�䵽�˵ײ������ɹ̶�����
			map->place_block();
		}
		return 1;//������������Ķ����ж�
	}
	map->draw_block();
	return 0;
}