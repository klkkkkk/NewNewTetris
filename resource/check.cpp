#include <stdio.h>
#include "block.h"
#include <vector>
#include <set>
#include "global.h"

int ifCrash(int** map, Block* block) {//���Ŀ��λ���Ƿ����з��飨��ǽ��
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

int fullLine(int** map, int line, int width) {//�Ƿ���һ��
	for (int i = 0; i < width; i++) {
		if (map[line][i] == 0) {
			return 0;
		}
	}
	return 1;
}

int clearLine(int** map, int height, int width) {//��ȥ�����У�����ͬʱ��ȥ���У�
	std::vector<int> index;
	int num = 0;
	for (int i = 1; i < height - 1; i++) {
		if (fullLine(map, i, width)) {//���������������е�����
			index.push_back(i);
			if (mode == 1 && i + 1 < height - 1) { index.push_back(i + 1); }
			num += 1;
		}
	}

	if (mode == 1) {//ȥ�أ�ֻ������ģʽ�Ż��õ�
		std::set<int> s(index.begin(), index.end());
		index.assign(s.begin(), s.end());
	}

	if (!index.empty()) {
		for (int i = 0; i < index.size(); i++) {//���������������������Ϸ�������������ƽ��
			for (int j = index[i]; j > 1; j--) {
				for (int k = 0; k < width; k++) {
					map[j][k] = map[j - 1][k];
				}
			}
		}
	}
	return num;
}