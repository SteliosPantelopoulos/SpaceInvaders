#include "Player.h"
#include "game.h"

void Player::checkBullet()
{
	//create an explosion if bullet is out of the map
	if (bullet)
	{
		if (!bullet->isActive())
		{
			explosion = new Explosion(game, getBullet()->getX(), getBullet()->getY() + 3, 10, "bullet");
			timeCreate = graphics::getGlobalTime();
			deleteBullet();
		}
	}
}

void Player::deleteBullet()
{
	delete bullet;
	bullet = nullptr;
	bulletInitialized = false;
}

Disk Player::getCollisionHull() const
{
	//hitbox for collisions
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = hitbox;
	return disk;
}

Player::Player(const Game& my_game)
	: GameObject(my_game)
{
}

Player::~Player()
{
	if (bullet)
		delete bullet;
	if (explosion)
		delete explosion;
}

void Player::draw()
{
	//hitbox if debug mode
	if (game.getDebugMode())
	{
		graphics::Brush brDebug;
		Disk hull = getCollisionHull();
		brDebug.texture = "";
		brDebug.fill_color[0] = 0.2f;
		brDebug.fill_color[1] = 0.9f;
		brDebug.fill_color[2] = 0.0f;
		brDebug.outline_opacity = 0.0f;
		brDebug.fill_opacity = 0.5f;
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brDebug);
	}
	//icon of player
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "player.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);

	if (bullet)
		bullet->draw();

	if (explosion)
		explosion->draw();
}

void Player::update()
{
	//position
	if (game.getControls()) 
	{
		if (graphics::getKeyState(graphics::SCANCODE_A))
			pos_x -= speed * graphics::getDeltaTime() / 20.0f;
		if (graphics::getKeyState(graphics::SCANCODE_D))
			pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}
	else
	{
		if (graphics::getKeyState(graphics::SCANCODE_LEFT))
			pos_x -= speed * graphics::getDeltaTime() / 20.0f;
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
			pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}
	//check if bullet is out of map
	if (pos_x - hitbox< LEFT_BOARDER) pos_x = LEFT_BOARDER + hitbox;
	if (pos_x +hitbox > RIGHT_BOARDER) pos_x = RIGHT_BOARDER - hitbox;
	checkBullet();

	//fire 
	if (graphics::getKeyState(graphics::SCANCODE_SPACE) && !bulletInitialized)
	{
		bullet = new Bullet(game, pos_x, pos_y, true);
		bulletInitialized = true;
		if(game.getAudio())
			graphics::playSound(std::string(ASSET_PATH) + "playerShoot.wav", 1, false);
	}

	if (bullet)
		bullet->update();

	if (explosion)
	{
		explosion->update();
		if (graphics::getGlobalTime() - timeCreate > 200)
		{
			delete explosion;
			explosion = nullptr;
		}
	}
}

void Player::init()
{
}