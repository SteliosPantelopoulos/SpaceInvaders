#pragma once
#include "gameobject.h"

class Explosion : public GameObject
{
	float pos_x, pos_y, size;
	std::string type;

public:
	Explosion(const class Game& my_game, float x, float y, float size, const char* type);
	~Explosion();
	void update() override;
	void draw() override;
	void init() override;
};