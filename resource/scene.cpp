#include "scene.h"
#include "global.h"
#include <set>
#include <cctype>

using namespace std;

//所有画面类
void Scene::cursorPos(coord& pos){
	COORD posPoint = { (ox + pos.x) * 2, oy + pos.y }; //设置坐标
	SetConsoleCursorPosition(hOut, posPoint);
}

/*----------------------------标题画面------------------------------*/
void Scene_Title::set_arrow(int x, int y) {
	arrow.x = x;
	arrow.y = y;
}

void Scene_Title::draw_arrow() {
	cursorPos(arrow);
	cout << "→";
}

void Scene_Title::delete_arrow() {
	cursorPos(arrow);
	cout << "  ";
}

/*----------------------------地图---------------------------*/
Scene_Map::Scene_Map(int x, int y, int h, int w) : Scene(x, y, h, w), map(h, vector<int>(w, 0)), block() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {//窗口边界
				map[i][j] = 1;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
}

void Scene_Map::reset(){
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j] > 1) {
				map[i][j] = 0;
			}
		}
	}
}

void Scene_Map::draw_map(){
	for (int i = 0; i < height; i++) {
		set_cursor(0,i);
		for (int j = 0; j < width; j++) {
			if (map[i][j] >= 1) {
				if (map[i][j] > 1) {
					setColor(map[i][j]);
				}
				draw_text("■");	// 墙体 
				setColor(7);
			}
			else {
				draw_text("□"); 	// 可移动区域 
			}
		}
	}
}

void Scene_Map::draw_block(){
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			set_cursor(y + j, x + i);
			if (Block::shapes[block.type][block.direction][i][j] == 1 
				&& x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0) {
				setColor(block.color);
				draw_text("■");
				setColor(7);
			}
		}
	}
	set_cursor(0, 0); 
}

void Scene_Map::clear_block(){
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			set_cursor(y + j, x + i);
			if (Block::shapes[block.type][block.direction][i][j] == 1 
				&& x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0) {
				draw_text("□");
			}
		}
	}
	set_cursor(0, 0);
}

bool Scene_Map::crash(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Block::shapes[block.type][block.direction][i][j] == 1 && map[block.x + i][block.y + j] >= 1) {
				return true;
			}
		}
	}
	return false;
}

void Scene_Map::place_block(){
	int x = block.x;
	int y = block.y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Block::shapes[block.type][block.direction][i][j] == 1 
				&& x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0) {
				map[x + i][y + j] = block.color;
			}
		}
	}
}

int Scene_Map::clear_line(){
	std::vector<int> index;
	int num = 0;
	for (int i = 1; i < height - 1; i++) {
		if (full_line(i)) {//从上往下搜索所有的满行
			index.push_back(i);
			if (mode == 1 && i + 1 < height - 1) { index.push_back(i + 1); }
			num += 1;
		}
	}

	if (mode == 1) {//去重，只有天命模式才会用到
		std::set<int> s(index.begin(), index.end());
		index.assign(s.begin(), s.end());
	}

	if (!index.empty()) {
		for (int i = 0; i < index.size(); i++) {//从上往下消除，将满行上方的所有行向下平移
			for (int j = index[i]; j > 1; j--) {
				for (int k = 0; k < width; k++) {
					map[j][k] = map[j - 1][k];
				}
			}
		}
	}
	return num;
}

bool Scene_Map::full_line(int line) {
	for (int i = 0; i < map[0].size(); i++) {
		if (map[line][i] == 0) {
			return false;
		}
	}
	return true;
}

vector<int> Scene_Map::operator[](int index) {
	return map[index];
}

/*----------------------------下一个界面---------------------------*/
void Scene_NextWindow::draw_map(){
	for (int i = 0; i < height; i++) {
		cursorPos(cursor);
		for (int j = 0; j < width; j++) {
			/*画一圈墙*/
			if (i == height - 1 || i == 0 || j == 0 || j == width - 1) {
				draw_text("■");
			}
			else {
				draw_text("  ");
			}
		}
		move_cursor(0, 1);
	}
}

void Scene_NextWindow::draw_block() {
	int x = block.x + 2;
	int y = block.y + 2;
	for (int i = 0; i < 4; i++) {
		set_cursor(y, x + i);
		for (int j = 0; j < 4; j++) {
			if (Block::shapes[block.type][block.direction][i][j] >= 1) {
				setColor(block.color);
				draw_text("■");
				setColor(7);
			}
			else {
				draw_text("  ");
			}
		}
	}
	set_cursor(0, 0);
}
/*----------------------------道具界面---------------------------*/
void Scene_Item::register_pos(){
	int pos = 0;
	for (auto& item : all_item) {
		item->pos = pos;
		pos += item->description.size() + space + 1;
	}
}

void Scene_Item::draw_item(){
	string text;
	set_cursor(0, 0);
	for (auto& item : all_item) {
		text = item->name + "(" + string(1,toupper(item->shortcut)) + ")  ×" + to_string(item->num) + "  ";
		draw_text(text);
		move_cursor(0, 1);
		for (auto& s : item->description) {
			draw_text(s);
			move_cursor(0, 1);
		}
		move_cursor(0, space);
	}
}

void Scene_Item::refresh(int index){
	auto item = all_item[index];
	set_cursor(0, item->pos);
	string text = item->name + "(" + string(1, toupper(item->shortcut)) + ")  ×" + to_string(item->num) + "  ";
	draw_text(text);
	move_cursor(0, 1);
	for (auto& s : item->description) {
		draw_text(s);
		move_cursor(0, 1);
	}
}

void Scene_Item::add_item(Item* item, int idx){
	all_item[idx] = item;
}
