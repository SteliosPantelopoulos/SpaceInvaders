#pragma once

#include "gameobject.h"
#include "bullet.h"
#include "explosion.h"


class Player : public GameObject, public Collidable
{
	float speed = 4.0;
	float pos_x = CANVAS_WIDTH /2, pos_y = CANVAS_HEIGHT - 30;
	float size = 35;
	float hitbox = size / 2;

	Bullet* bullet = nullptr;
	bool bulletInitialized = false;
	Explosion* explosion = nullptr;
	float timeCreate;

	graphics::Brush br;
	
public:
	Player(const class Game& my_game);
	~Player();
	void draw() override;
	void update() override;
	void init() override;

	void checkBullet();
	void deleteBullet();
	Disk getCollisionHull() const override;

	float getX() { return pos_x; }
	float getY() { return pos_y; }
	float getSize() { return size; }
	Bullet* getBullet() { return bullet; }
};