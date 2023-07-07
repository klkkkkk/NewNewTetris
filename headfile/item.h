#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "global.h"

using std::string;
using std::vector;
class Scene;
class Scene_Item;

class Item {
public:
	string name;
protected:
	int num;
	char shortcut;
	bool using_state;
	vector<string> description;
	int pos;
	int turn;
public:
	friend class Scene;
	friend class Scene_Item;
	Item() {};
	virtual bool use() = 0;
	virtual bool check_get(int row = 0) = 0;
	virtual void check_effect() = 0;
	virtual ~Item() {};

	bool is_using() { return using_state; }
	int own() { return num; }
	void clear();
};

class MoJu : public Item {
private:
	int count;
public:
	MoJu();
	virtual bool use();
	virtual bool check_get(int row);
	virtual void check_effect();
};

class BuDing : public Item {
public:
	BuDing();
	virtual bool use();
	virtual bool check_get(int row);
	virtual void check_effect();
};

class SiKao : public Item {
public:
	SiKao();
	virtual bool use();
	virtual bool check_get(int row);
	virtual void check_effect();
};