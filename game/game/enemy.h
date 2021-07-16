#pragma once
#include "gameobject.h"
#include "bullet.h"

class Enemy : public GameObject, public Collidable
{
	float pos_x, pos_y;
	float speed;
	float size, hitbox, spaceBetween = 4;
	int number;
	bool alive = true;
	float timeLastMovement= 0;
	Bullet* bullet = nullptr;
	bool bulletInitialized = false;
	bool checkUnder();

public:
	Enemy(const class Game& my_game, int i);
	~Enemy();
	void update() override;
	void draw() override;
	void init() override;

	Disk getCollisionHull() const override;
	void checkBullet();
	void deleteBullet();
	bool isAlive() { return alive; }
	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getSize() { return size; }
	Bullet* getBullet() { return bullet; }
};