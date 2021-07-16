#include "enemy.h"
#include "game.h"
#include <iostream>

Enemy::Enemy(const Game& my_game, int i)
	: GameObject(my_game)
{
	//number is the position of the enemy in the array 
	//column = number / COLUMNS
	//row = number % COLUMNS
	number = i;
	init();
}

Enemy::~Enemy()
{
	if (bullet)
		delete bullet;
}

void Enemy::update()
{	
	//movement
	if (pos_x > RIGHT_BOARDER - (COLUMNS - number%COLUMNS) * (size + spaceBetween) - hitbox)
	{
		pos_x -= speed * graphics::getDeltaTime();
		pos_y += size;
		speed = -speed;
	}
	else if (pos_x < LEFT_BOARDER + hitbox + number % COLUMNS * (size + spaceBetween))
	{
		pos_x -= speed * graphics::getDeltaTime();
		speed = -speed;
	}
	else
	{
		pos_x += speed * graphics::getDeltaTime();
	}
		checkBullet();
	//fire
	if (!bulletInitialized && checkUnder())
	{
		float randomNumber = floor(850 * rand0to1());
		if (randomNumber == 5)
		{
			bullet = new Bullet(game, pos_x, pos_y, false);
			bulletInitialized = true;
		}
	}
	if (bullet)
		bullet->update();
}

void Enemy::draw()
{
	graphics::Brush br;
	//draw the hitbox of the enemy
	if (game.getDebugMode())
	{
		graphics::Brush brDebug;
		Disk hull = getCollisionHull();
		brDebug.texture = "";
		brDebug.fill_color[0] = 0.9f;
		brDebug.fill_color[1] = 0.2f;
		brDebug.fill_color[2] = 0.0f;
		brDebug.outline_opacity = 0.0f;
		brDebug.fill_opacity = 0.5f;
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brDebug);
	}
	//image to represent movement change from open to close
	int x = (int)pos_x - number % COLUMNS *(size+spaceBetween);
	if (number / COLUMNS == 0)
	{
		if (x % 20 < 10)
			br.texture = std::string(ASSET_PATH) + "enemy1open.png";
		else
			br.texture = std::string(ASSET_PATH) + "enemy1close.png";
	}
	else if (number / COLUMNS == 1)
	{
		if (x % 20 < 10)
			br.texture = std::string(ASSET_PATH) + "enemy2open.png";
		else
			br.texture = std::string(ASSET_PATH) + "enemy2close.png";
	}
	else
	{
		if (x % 20 < 10)
			br.texture = std::string(ASSET_PATH) + "enemy3open.png";
		else
			br.texture = std::string(ASSET_PATH) + "enemy3close.png";
	}
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, br);

	if (bullet)
		bullet->draw();
}

void Enemy::init()
{
	size = 35;
	pos_x = (CANVAS_WIDTH / 2) - (COLUMNS/2) * (size + spaceBetween) + (number % COLUMNS) * (size + spaceBetween);
	pos_y = 100 + (number/COLUMNS)*(size +spaceBetween);
	hitbox = size / 2;
	speed = 0.05f;
}

bool Enemy::checkUnder()
{	
	//check if all the enemies under this enemy are dead
	if (game.getEnemy(number))
	{
		int i= number + 11;
		while (i < 44) 
		{
			if (game.getEnemy(i))
				return false;
			i += number + 11;
		}
		return true;
	}
	return false;
}

void Enemy::checkBullet()
{	
	//check if bullet is inside canvas
	if (bullet)
	{
		if (!bullet->isActive())
			deleteBullet();
	}
}

void Enemy::deleteBullet()
{
	delete bullet;
	bullet = nullptr;
	bulletInitialized = false;
}

Disk Enemy::getCollisionHull() const
{
	//hitbox for collisions
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = hitbox;
	return disk;
}