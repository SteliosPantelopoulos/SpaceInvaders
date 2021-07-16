#pragma once
#include "gameobject.h"
#include "config.h"
#include "graphics.h"

class Shield :public GameObject, public Collidable {
	int hp = 4, num;
	float posX=250, posY=400;
	graphics::Brush brush;

public:
	Shield(const class Game& mygame, int i);
	~Shield();
	void update()override;
	void draw() override;
	void init() override;

	Disk getCollisionHull() const override;
	int getNum() { return num; }
	void detuctLife() { hp--; }
	int getLife() {return hp; }
}; 