#include "shield.h"
#include "game.h"
#include <iostream>

Disk Shield::getCollisionHull() const
{
	//hitbox for collisions
	Disk disk;
	disk.cx = posX;
	disk.cy = posY;
	disk.radius = 60;
	return disk;
}

void Shield::update()
{
}

void Shield::draw()
{

	int x = 4* num * 55; 
	//hitbox if debug mode
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
		graphics::drawDisk(hull.cx , hull.cy, hull.radius, brDebug);
	}
	//differnt icons for every hp
	if (getLife() == 4) {
		brush.texture = std::string(ASSET_PATH) + "shield.png";
		brush.outline_opacity = 0.0f;
		graphics::drawRect(posX, posY, 100, 100, brush);
	}
	else if (getLife() == 3) {
		brush.texture = std::string(ASSET_PATH) + "shield1.png";
		brush.outline_opacity = 0.0f;
		graphics::drawRect(posX  , posY, 100, 100, brush);
	}
	else if (getLife() == 2) {
		brush.texture = std::string(ASSET_PATH) + "shield2.png";
		brush.outline_opacity = 0.0f;
		graphics::drawRect(posX , posY, 100, 100, brush);
	}
	else if (getLife() == 1) {
		brush.texture = std::string(ASSET_PATH) + "shield3.png";
		brush.outline_opacity = 0.0f;
		graphics::drawRect(posX  , posY, 100, 100, brush);
	}
}

void Shield::init()
{
}

Shield::Shield(const Game& mygame, int i) 
	:GameObject(mygame)
{	
	num = i;
	posX += 4 * num * 55;
}

Shield::~Shield()
{
} 