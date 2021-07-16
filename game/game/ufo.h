#pragma once
#include "gameobject.h"
#include "config.h"

class Ufo : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size, hitbox;
	bool active = true;

public:
	Ufo(const class Game& my_game);
	~Ufo();
	void update() override;
	void draw() override;
	void init();

	Disk getCollisionHull() const override;

	bool isActive() { return active; }
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getSize() { return size; }
};
