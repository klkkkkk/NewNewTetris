#include "item.h"

void Item::clear(){
	num = 0;
	using_state = false;
	turn = 0;
}

MoJu::MoJu(){
	name = "����ģ��";
	num = 0;
	shortcut = ITEM_1_SHORTCUT;
	using_state = false;
	string text;
	text = "���ã��������������ɺ͵�ǰ����һ����";
	description.push_back(text);
	text = "��ȡ��ʽ�����õ��߸�Ԥ���������������" + std::to_string(ITEM_1_VAL) + "����ͬ�ķ��顣";
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
	if (count >= ITEM_1_VAL) {//���һ��������ֱ�����㣬������������3�������
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
	name = "����";
	num = 0;
	shortcut = ITEM_2_SHORTCUT;
	using_state = false;
	string text;
	text = "���ã�����ǰ������һ��С���顣";
	description.push_back(text);
	text = "��ȡ��ʽ������"+ std::to_string(ITEM_2_VAL) + "��û�������κ�һ�С���ǰ��ʣ" + 
		std::to_string(ITEM_2_VAL - turn) + "��";
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
	string text = "��ȡ��ʽ������" + std::to_string(ITEM_2_VAL) + "��û�������κ�һ�С���ǰ��ʣ" +
		std::to_string(ITEM_2_VAL - turn) + "��";
	description.push_back(text);
	return get;
}

void BuDing::check_effect(){
	using_state = false;
}

SiKao::SiKao() {
	name = "����˼��";
	num = 0;
	shortcut = ITEM_3_SHORTCUT;
	using_state = false;
	string text;
	text = "���ã���ת��ǰ�����ʹ�������Ϊ��һ����״�ķ��顣";
	description.push_back(text);
	text = "��ȡ��ʽ��һ��������" + std::to_string(ITEM_3_VAL) + "�л����ϡ�";
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
