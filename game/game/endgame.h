#pragma once
#include "graphics.h"
#include "config.h"

class EndGame
{
	int gameResult = -1;
	int choise = 1;
	int state = 0;

public:
	EndGame(int result); // 0 win, 1 loss, 2 choose from menu
	~EndGame();
	void update();
	void draw();
	void init();

	int getState() { return state; } //if state is true restart game else end application
};