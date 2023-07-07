#pragma once
#include "block.h"
#include "item.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Item;

class Scene {
protected:
	int ox;
	int oy;
	int height;
	int width;
	struct coord {
		int x;
		int y;
		coord() { x = 0; y = 0; }
		coord(int _x, int _y) { x = _x; y = _y; }
	};
	coord cursor;

	virtual void cursorPos(coord& pos);
public:
	Scene(int x, int y, int h, int w) {
		ox = x;
		oy = y;
		height = h;
		width = w;
	}
	void set_cursor(int x, int y) { cursor.x = x; cursor.y = y; cursorPos(cursor); }
	void move_cursor(int x, int y) { cursor.x += x; cursor.y += y; cursorPos(cursor);}
	void draw_text(string text, bool enter = false) {std::cout << text; if (enter) std::cout << std::endl; }
};

class Scene_Title : public Scene {
private:
	coord arrow;
public:
	Scene_Title(int x, int y, int h, int w) : Scene(x, y, h, w){
		arrow.x = TITLE_CURSOR_X;
		arrow.y = TITLE_CURSOR_Y;
	}
	void set_arrow(int x, int y);
	void draw_arrow();
	void delete_arrow();
};

class Scene_Map : public Scene {
private:
	bool full_line(int line);
public:
	vector<vector<int>> map;
	Block block;
public:
	Scene_Map(int x, int y, int h, int w);
	void reset();
	void draw_map();
	void draw_block();
	void clear_block();
	bool crash();
	void place_block();
	int clear_line();
	vector<int> operator[](int index);
};

class Scene_NextWindow : public Scene {
public:
	Block block;
public:
	Scene_NextWindow(int x, int y, int h, int w) : Scene(x, y, h, w), block() {}
	void draw_map();
	void draw_block();
};

class Scene_Item : public Scene {
private:
	int space;
public:
	vector<Item*> all_item;
public:
	Scene_Item(int x, int y, int h, int w) : Scene(x, y, h, w) { space = 1; all_item.resize(ITEM_TYPE); }
	void draw_item();
	void register_pos();
	void refresh(int index);
	void add_item(Item* item, int idx);
};