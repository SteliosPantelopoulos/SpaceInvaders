#pragma once
#include "graphics.h"
#include "config.h"


class Settings
{
	bool controlsChoise = true;
	bool audioChoise = true;
	int state = 0;
public:
	Settings();
	~Settings();
	void update();
	void draw();
	void init();	

	int getState() {return state;}
	bool getControls() { return controlsChoise; } //true for wasd false for arrows
	bool getAudio() { return audioChoise; }
};