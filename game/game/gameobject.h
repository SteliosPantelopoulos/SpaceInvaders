#pragma once
#include "graphics.h"
#include "config.h"
#include "util.h"

class Collidable
{
public:
	virtual Disk getCollisionHull() const = 0;
};


class GameObject
{
protected:
	const class Game & game;

public:
	GameObject(const class Game & my_game);
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void init() = 0;
};