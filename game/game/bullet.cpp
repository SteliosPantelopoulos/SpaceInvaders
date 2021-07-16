#include "bullet.h"
#include "game.h"
#include <iostream>

void Bullet::update()
{
	//controls the motion of the bullet and if is inside the canvas
	pos_y += speed * graphics::getDeltaTime();
	if (pos_y < 0 || pos_y>CANVAS_HEIGHT)
		active = false;
}

void Bullet::draw()
{
	//draws bullet
	//different bullets for players and enemies
	graphics::Brush br;
	if (player)
	{
		br.texture = "";
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.outline_opacity = 0.0f;
		graphics::drawDisk(pos_x, pos_y, hitbox, br);
	}
	else
	{
		br.texture = "";
		br.fill_color[0] = 0.5f;
		br.fill_color[1] = 0.1f;
		br.fill_color[2] = 0.9f;
		br.outline_opacity = 0.0f;
		graphics::drawRect(pos_x, pos_y, hitbox, hitbox*3, br);
	}
}

void Bullet::init()
{
}

Bullet::Bullet(const class Game& my_game, float x, float y, bool player) 
	: GameObject(my_game)
{
	//pos_x, pos_y cordinates of bullet
	//if the bullet is created by a player change the way of the bullet and double its speed
	pos_x = x;
	pos_y = y;
	this->player = player;
	if (this->player) 
		speed = -2*speed;
}

Bullet::~Bullet()
{
}

Disk Bullet::getCollisionHull() const
{
	//used for collisions
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = hitbox;
	return disk;
}
