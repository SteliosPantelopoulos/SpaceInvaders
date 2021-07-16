#include "explosion.h"
#include "game.h"

void Explosion::update()
{
}

void Explosion::draw()
{
	//draw deffirent animation for explosion of player, bullet, enemy
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	if (type == "enemy")
	{
		br.texture = std::string(ASSET_PATH) + "enemyExplosion.png";
		graphics::drawRect(pos_x, pos_y, size, size, br);
	}
	else if (type == "bullet")
	{
		br.texture = std::string(ASSET_PATH) + "bulletExplosion.png";
		graphics::drawRect(pos_x, pos_y, size, size, br);
	}
}

void Explosion::init()
{
	//generate sound if audio is ON
	if (game.getAudio())
	{
		if (type == "player")
			graphics::playSound(std::string(ASSET_PATH) + "playerKilled.wav", 1, false);
		else if (type == "enemy")
			graphics::playSound(std::string(ASSET_PATH) + "enemyKilled.wav", 1, false);
		else if (type == "bullet")
			graphics::playSound(std::string(ASSET_PATH) + "bulletKilled.mp3", 1, false);
	}
}

Explosion::Explosion(const class Game& my_game, float x, float y, float size,const char* type)
	: GameObject(my_game)
{
	pos_x = x;
	pos_y = y;
	this->size = size;
	this->type = type;
	init();
}

Explosion::~Explosion()
{
}