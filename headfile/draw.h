#pragma once
#include "block.h"

void drawInit(int h, int w);
void mapInit(int** map);
void drawMap(int** map);
void cleanBlock(Block block);
void drawBlock(Block block);
void Cursorpos(int x, int y);
void cleanLine(int** map);
void drawNext_window();
void drawNext(Block block);
void drawText(int x, int y, std::string text);
void drawItem(int x, int y);
void drawItemIntro(int x, int y);