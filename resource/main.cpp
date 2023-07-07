#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>//getch()函数
#include <stdlib.h>//system()函数
#include <time.h>
#include "global.h"
#include "gameplay.h"
using namespace std;

extern void scene_title();

string text = "";
int Block::shapes[BLOCKKIND + 1][4][4][4];

int main() {
	/* 初始化*/
	Block::set_shape();
	Scene_Map map(MAIN_OX, MAIN_OY, MAIN_HEIGHT, MAIN_WIDTH);
	Scene_NextWindow next_window(MAIN_OX + MAIN_WIDTH, MAIN_OY, NEXT_HEIGHT, NEXT_WIDTH);
	Scene scene_score(SCORE_OX, SCORE_OY, SCORE_HEIGHT, SCORE_WIDTH);
	Scene_Item scene_item(ITEM_OX, ITEM_OY, ITEM_HEIGHT, ITEM_WIDTH);
	MoJu moju;
	BuDing buding;
	SiKao sikao;
	scene_item.add_item(&moju, ITEM_1);
	scene_item.add_item(&buding, ITEM_2);
	scene_item.add_item(&sikao, ITEM_3);
	scene_item.register_pos();

	Game game(&map, &next_window, &scene_score, &scene_item);
start:
	mode = -1;
	map.reset();
	system("cls");
	scene_title();
	system("cls");

	score = 0;
	level = 0;
	moju.clear();
	buding.clear();
	sikao.clear();

	map.draw_map();//画出对应格子
	next_window.draw_map();
	game.refresh_score();

	switch (mode) {
	case 0:
		text = "经典模式"; break;
	case 1:
		text = "天命模式"; break;
	case 2://道具模式专用
		text = "道具模式";
		scene_item.draw_item();
	}
	map.set_cursor(-6, 2);
	map.draw_text(text);

	/*产生方块*/
	game.new_block();
	map.draw_block();
	next_window.draw_block();

	clock_t start, end, level_up_text_time = 0;
	int act = 0;//记录动作

	while (true) {
		start = clock();
		end = clock();
		if (level_up && (clock() - level_up_text_time >= 2500)) {
			text = "         ";
			scene_score.set_cursor(8, 0);
			scene_score.draw_text(text);
			level_up = false;
		}
		if (get_item && clock() - item_time >= 2000) {
			text = "                                         ";
			scene_score.set_cursor(8, 3);
			scene_score.draw_text(text);
			get_item = false;
		}

		while (end - start <= speed[level]) {//允许操作的时间间隔
			act = game.wait_action(-1);
			switch (act) {
			case BOTTOM: down_press = false; break;
			case ITEM_1: game.use_item(ITEM_1); break;
			case ITEM_2: game.use_item(ITEM_2); break;
			case ITEM_3: game.use_item(ITEM_3); break;
			}
			end = clock();
			if (act == BOTTOM || down_press) { break; }//如果落到底部或加速下落直接结束本次循环
		}

		if (down_press) { down_press = false; continue; }

		if (game.wait_action(80) == BOTTOM) {//操作时间结束，方块自动下落一格
			game.clear_event();
			same = (int)(map.block.get_type() == next_window.block.get_type());
			if (mode == 2 && scene_item.all_item[ITEM_1]->check_get(same)) {
				text = "获得" + scene_item.all_item[ITEM_1]->name + "×1！";
				game.item_prompt(text);
				scene_item.refresh(ITEM_1);
			}
			scene_item.all_item[ITEM_1]->check_effect();
			scene_item.all_item[ITEM_2]->check_effect();
			scene_item.all_item[ITEM_3]->check_effect();
			//读取下一个方块
			game.next_block();

			map.draw_block();
			next_window.draw_block();

			if (map.crash()) {//新方块碰到了已有方块，游戏结束
				map.set_cursor(0, 25);
				map.draw_text("你挂了。按任意键返回标题画面。");
				break;
			}
		}

		if (level_up && level_up_text_time == 0) {//进入下一关
			level_up_text_time = clock();
		}
	}
	while (true) {
		if (_kbhit()) {//检查是否按下某键,回到标题画面
			_getch();
			mode = -1;
			goto start;
		}
	}
	return 0;

}

