#include <stdio.h>
#include "block.h"
#include <vector>
#include <set>
#include "global.h"

int ifCrash(int** map, Block* block) {//检查目标位置是否已有方块（或墙）
	int x = block->x;
	int y = block->y;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block->shapes[block->type][i][j] >= 1 && map[x + i][y + j] >= 1) {
				return 1;
			}
		}
	}
	return 0;
}

int fullLine(int** map, int line, int width) {//是否满一行
	for (int i = 0; i < width; i++) {
		if (map[line][i] == 0) {
			return 0;
		}
	}
	return 1;
}

int clearLine(int** map, int height, int width) {//消去满的行（可以同时消去多行）
	std::vector<int> index;
	int num = 0;
	for (int i = 1; i < height - 1; i++) {
		if (fullLine(map, i, width)) {//从上往下搜索所有的满行
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