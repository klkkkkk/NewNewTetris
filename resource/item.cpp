#include "item.h"

void Item::clear(){
	num = 0;
	using_state = false;
	turn = 0;
}

MoJu::MoJu(){
	name = "方块模具";
	num = 0;
	shortcut = ITEM_1_SHORTCUT;
	using_state = false;
	string text;
	text = "作用：将下两个方块变成和当前方块一样。";
	description.push_back(text);
	text = "获取方式：不用道具干预的情况下连续出现" + std::to_string(ITEM_1_VAL) + "个相同的方块。";
	description.push_back(text);
	pos = 0;
	turn = 0;
}

bool MoJu::use(){
	if (num <= 0) {
		return false;
	}
	num -= 1;
	using_state = true;
	turn += 2;
	return true;
}

bool MoJu::check_get(int row){
	count = (same == 1 && !using_state) ? count + 1: 0;
	if (count >= ITEM_1_VAL) {//达成一次条件便直接清零，避免连续出现3个的情况
		num += 1;
		count = 0;
		return true;
	}
	return false;
}

void MoJu::check_effect(){
	if (turn > 0) {
		turn -= 1;
		if (turn == 0) {
			using_state = false;
		}
	}
}

BuDing::BuDing() {
	name = "补丁";
	num = 0;
	shortcut = ITEM_2_SHORTCUT;
	using_state = false;
	string text;
	text = "作用：将当前方块变成一个小方块。";
	description.push_back(text);
	text = "获取方式：连续"+ std::to_string(ITEM_2_VAL) + "轮没有消除任何一行。当前还剩" + 
		std::to_string(ITEM_2_VAL - turn) + "轮";
	description.push_back(text);
	pos = 0;
	turn = 0;
}

bool BuDing::use(){
	if (num <= 0) {
		return false;
	}
	num -= 1;
	using_state = true;
	return true;
}

bool BuDing::check_get(int row){
	bool get = false;
	if (row > 0) {
		turn = 0;
	}
	else {
		turn += 1;
		if (turn == ITEM_2_VAL) {
			num += 1;
			turn = 0;
			get = true;
		}
	}
	description.pop_back();
	string text = "获取方式：连续" + std::to_string(ITEM_2_VAL) + "轮没有消除任何一行。当前还剩" +
		std::to_string(ITEM_2_VAL - turn) + "轮";
	description.push_back(text);
	return get;
}

void BuDing::check_effect(){
	using_state = false;
}

SiKao::SiKao() {
	name = "快速思考";
	num = 0;
	shortcut = ITEM_3_SHORTCUT;
	using_state = false;
	string text;
	text = "作用：旋转当前方块会使其随机变为另一种形状的方块。";
	description.push_back(text);
	text = "获取方式：一次性消除" + std::to_string(ITEM_3_VAL) + "行或以上。";
	description.push_back(text);
	pos = 0;
	turn = 0;
}

bool SiKao::use(){
	if (num <= 0) {
		return false;
	}
	num -= 1;
	using_state = true;
	return true;
}

bool SiKao::check_get(int row){
	if (row >= ITEM_3_VAL) {
		num += 1;
		return true;
	}
	return false;
}

void SiKao::check_effect(){
	using_state = false;
}
