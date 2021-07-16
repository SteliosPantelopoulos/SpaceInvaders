#pragma once
#include "gameobject.h"
#include "explosion.h"

class Bullet : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed = 0.1f;
	float hitbox = 2.5f;
	bool active = true;
	bool player;
	Explosion* explosion;

public:
	Bullet(const class Game& my_game, float x, float y, bool player);
	~Bullet();
	void update() override;
	void draw() override;
	void init() override;

	bool isActive() { return active; }
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	Disk getCollisionHull() const override;
};