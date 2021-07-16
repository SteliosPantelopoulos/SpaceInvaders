#include "ufo.h"
#include "game.h"

Ufo::Ufo(const Game& my_game)
	: GameObject(my_game)
{
	init();
}

Ufo::~Ufo()
{
}

void Ufo::update()
{
	//movement
	pos_x += speed * graphics::getDeltaTime();

	if (pos_x + 1.1 * size < 0)
		active = false;
	//change audio every millisecond to create effect
	if (game.getAudio())
	{
		if (fmod(graphics::getGlobalTime(), 2 < 1))
			graphics::playSound(std::string(ASSET_PATH) + "ufoHighpitch.wav", 1, false);
		else
			graphics::playSound(std::string(ASSET_PATH) + "ufoLowpitch", 1, false);
	}
}

void Ufo::draw()
{
	graphics::Brush br;
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
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brDebug);
	}
	//icon
	br.texture = std::string(ASSET_PATH) + "ufo.png",
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, 1.5*size, br);
}

void Ufo::init()
{
	size = 30;
	hitbox = size/2;
	pos_x = CANVAS_WIDTH + 1.1*size;
	pos_y = 50;
	speed = -0.2f;
}

Disk Ufo::getCollisionHull() const
{
	//hitbox for collisionts
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = hitbox;
	return disk;
}