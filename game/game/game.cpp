#include "game.h"
#include <iostream>

void Game::spawnEnemy()
{
	//spawns enemies
	if (!enemiesInitialized)
	{
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			enemies[i] = new Enemy(*this, i);
	}
}

void Game::spawnShield()
{
	//spawn shields
	if (!shieldInitialized)
		for (int i = 0; i < SHIELD_NUM; i++)
			shields[i] = new Shield(*this, i);
}

void Game::collisionDetectionForEnemy()
{
	//collision detection for enemy and player's bullets if happens delete enemy and bullet
	if(player)
	{
		if (player->getBullet())
		{
			Disk d1 = player->getBullet()->getCollisionHull();
			for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			{
				if (enemies[i])
				{
					Disk d2 = enemies[i]->getCollisionHull();
					float dx, dy, sradius;
					dx = d1.cx - d2.cx;
					dy = d1.cy - d2.cy;
					sradius = d1.radius + d2.radius;
					if (sqrt(dx * dx + dy * dy) < sradius)
					{
						if (i / COLUMNS >= 2)
							score += 20;
						else if (i / COLUMNS == 1)
							score += 30;
						else
							score += 40;
						player->deleteBullet();
						createExplosionEnemy(i);
						delete enemies[i];
						enemies[i] = nullptr;
					}
				}
			}
		}
	}
}

void Game::collisionDetectionForPlayer()
{
	//colision detection for player and enemy's bullets if happens decrease lifes and delete bullet
	if (player)
	{
		Disk d1 = player->getCollisionHull();
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			if (enemies[i])
			{
				if (enemies[i]->getBullet())
				{
					Disk d2 = enemies[i]->getBullet()->getCollisionHull();
					float dx, dy, sradius;
					dx = d1.cx - d2.cx;
					dy = d1.cy - d2.cy;
					sradius = d1.radius + d2.radius;
					if (sqrt(dx * dx + dy * dy) < sradius)
					{
						enemies[i]->deleteBullet();
						lifes--;
						createExplosionPlayer();
					}
				}
			}
		}
	}
}

void Game::collisionDetectionForBullets()
{
	//collision detection for player's bullets and enemy's bullets if happens delete both bullets
	if (player)
	{
		if (player->getBullet())
		{
			Disk d1 = player->getBullet()->getCollisionHull();
			for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			{
				if (enemies[i])
				{
					if (enemies[i]->getBullet())
					{
						Disk d2 = enemies[i]->getBullet()->getCollisionHull();
						float dx, dy, sradius;
						dx = d1.cx - d2.cx;
						dy = d1.cy - d2.cy;
						sradius = d1.radius + d2.radius;
						if (sqrt(dx * dx + dy * dy) < sradius)
						{
							createExplosionBullet();
							enemies[i]->deleteBullet();
							player->deleteBullet();
						}
					}
				}
			}
		}
	}
}

void Game::collisionDetectionForEnemyPlayer()
{
	//collision detection for enemy and player if happens game over
	if (player)
	{
		Disk d1 = player->getCollisionHull();
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			if (enemies[i])
			{
				Disk d2 = enemies[i]->getCollisionHull();
				float dx, dy, sradius;
				dx = d1.cx - d2.cx;
				dy = d1.cy - d2.cy;
				sradius = d1.radius + d2.radius;
				if (sqrt(dx * dx + dy * dy) < sradius)
					lifes = 0;
			}
		}
	}
}

void Game::collisionDetectionForUfo()
{
	//collision detection for player's bullets and ufo if happens give a random score and delete both ufo and the bullet
	if (player)
	{
		if (player->getBullet())
		{
			Disk d1 = player->getBullet()->getCollisionHull();
			if (ufo)
			{
				Disk d2 = ufo->getCollisionHull();
				float dx, dy, sradius;
				dx = d1.cx - d2.cx;
				dy = d1.cy - d2.cy;
				sradius = d1.radius + d2.radius;
				if (sqrt(dx * dx + dy * dy) < sradius)
				{
					score += floor(1000 * rand0to1()) / 10;
					createExplosionUfo();
					delete ufo;
					ufo = nullptr;
					ufoInitialized = false;
					player->deleteBullet();
				}
			}

		}
	}
}

void Game::collisionDetectionForShieldEnemy()
{
	//collision detection for enemy's bullets and shields if happens delete bullet and decrease shield hp by one
	for (int j = 0; j < SHIELD_NUM; j++) 
	{
		if (shields[j]) 
		{
			Disk shield = shields[j]->getCollisionHull();

			for (int i = 0; i < NUMBER_OF_ENEMIES; i++) 
			{
				if (enemies[i]) 
				{
					if (enemies[i]->getBullet()) 
					{
						Disk enemy = enemies[i]->getBullet()->getCollisionHull();
						float dx, dy, sradius;
						dx = shield.cx - enemy.cx;
						dy = shield.cy - enemy.cy;
						sradius = shield.radius + enemy.radius;
						if (sqrt(dx * dx + dy * dy) < sradius) 
						{
							enemies[i]->deleteBullet();
							shields[j]->detuctLife();
							if (shields[j]->getLife() == 0) 
							{
								delete shields[j];
								shields[j] = nullptr;
							}
						}
					}
				}
			}
		}
	}
}

void Game::collisionDetectionForShieldPlayer()
{
	//collision detection for player's bullets and shields if happens delete bullet and decrease shield's hp by one
	for (int j = 0; j < SHIELD_NUM; j++) 
	{
		if (shields[j]) 
		{
			Disk shield = shields[j]->getCollisionHull();
			if (player)
			{
				if (player->getBullet())
				{
					Disk d1 = player->getBullet()->getCollisionHull();
					float dx, dy, sradius;
					dx = shield.cx - d1.cx;
					dy = shield.cy - d1.cy;
					sradius = shield.radius + d1.radius;
					if (sqrt(dx * dx + dy * dy) < sradius)
					{
						player->deleteBullet();
						shields[j]->detuctLife();
						if (shields[j]->getLife() == 0)
						{
							delete shields[j];
							shields[j] = nullptr;
						}
					}
				}
			}
		}
	}
}

void Game::createExplosionEnemy(int i)
{
	//triggered when an enemy is hit
	explosion = new Explosion(*this, enemies[i]->getX(), enemies[i]->getY(), enemies[i]->getSize(), "enemy");
	timeCreate = graphics::getGlobalTime();
}

void Game::createExplosionPlayer()
{
	//triggered when player is hit
	explosion = new Explosion(*this, player->getX(), player->getY(), player->getSize(), "player");
	timeCreate = graphics::getGlobalTime();
}

void Game::createExplosionBullet()
{
	//triggered when two bullets hit
	explosion = new Explosion(*this, player->getBullet()->getX(), player->getBullet()->getY(), 10, "bullet");
	timeCreate = graphics::getGlobalTime();
}

void Game::createExplosionUfo()
{
	//triggered when an ufo is hit
	explosion = new Explosion(*this, ufo->getX(), ufo->getY(), ufo->getSize(), "enemy");
	timeCreate = graphics::getGlobalTime();
}

void Game::refreshMenuChoise()
{
	//triggered if we return from settings to main menu
	//or if we choose restart game from end screen menu
	if (endgame)
	{
		if (endgame->getState() == 1)
		{
			delete endgame;
			endgame = nullptr;
			exitGame = false;
			restartGame();
		}
	}

	if (settings)
		if (settings->getState() == 1)
		{
			delete settings;
			settings = nullptr;
			startSettings = false;
		}
}

void Game::restartGame()
{
	//delete all game objects, refill lifes
	if (player)
	{
		delete player;
		player = nullptr;
	}

	if (enemiesInitialized)
	{
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	if (explosion)
	{
		delete explosion;
		explosion = nullptr;
	}
		

	if (ufo)
	{
		delete ufo;
		ufo = nullptr;
	}

	if (shieldInitialized)
	{
		for (int i = 0; i < SHIELD_NUM; i++)
		{
			delete shields[i];
			shields[i] = nullptr;
		}
	}

	lifes = 3;
	startGame = true;
	playerInitialized = false, enemiesInitialized = false, ufoInitialized = false, shieldInitialized = false;
}

void Game::checkUfo()
{
	//check if ufo is inside canvas, if not delete it
	if (!ufo->isActive())
	{
		delete ufo;
		ufo = nullptr;
		ufoInitialized = false;
	}
}

void Game::update()
{
	refreshMenuChoise();
	if(!startGame && !startSettings && !exitGame)
	{
		//check if buttons are clicked
		graphics::MouseState mouse;
		graphics::getMouseState(mouse);

		if (mouse.cur_pos_x >= 540 && mouse.cur_pos_x <= 670 && mouse.cur_pos_y >= 380 && mouse.cur_pos_y <= 400)
			if (mouse.button_left_pressed)
				startGame = true;

		if (mouse.cur_pos_x >= 550 && mouse.cur_pos_x <= 650 && mouse.cur_pos_y >= 425 && mouse.cur_pos_y <= 440)
			if (mouse.button_left_pressed)
				startSettings = true;

		if (mouse.cur_pos_x >= 550 && mouse.cur_pos_x <= 650 && mouse.cur_pos_y >= 465 && mouse.cur_pos_y <= 485)
			if (mouse.button_left_pressed)
				exitGame = true;
	}
	if (startGame)
	{
		//initialize game objects
		if (!playerInitialized)
		{
			player = new Player(*this);
			playerInitialized = true;
		}
		if (player)
			player->update();

		if (!enemiesInitialized)
		{
			spawnEnemy();
			enemiesInitialized = true;
		}

		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			if (enemies[i])
				enemies[i]->update();

		if (explosion)
		{
			explosion->update();
			if (graphics::getGlobalTime() - timeCreate > 200)
			{
				delete explosion;
				explosion = nullptr;
			}
		}

		if (!ufoInitialized)
		{
			float randomNumber = floor(1000 * rand0to1());
			if (randomNumber == 5)
			{
				ufo = new Ufo(*this);
				ufoInitialized = true;
			}
		}

		if (ufo) 
		{
			ufo->update();
			checkUfo();
		}

		if (!shieldInitialized)
		{
			spawnShield();
			shieldInitialized = true;
		}

		//check for collisions
		collisionDetectionForEnemy();
		collisionDetectionForPlayer();
		collisionDetectionForBullets();
		collisionDetectionForEnemyPlayer();
		collisionDetectionForUfo();
		collisionDetectionForShieldEnemy();
		collisionDetectionForShieldPlayer();

		//check if game is over WIN or LOSS
		if (isDead())
		{
			startGame = false;
			exitGame = true;
		}

		if (enemiesDead())
		{
			startGame = false;
			exitGame = true;
		}
	}
	else if (startSettings)
	{
		if (!settings)
			settings = new Settings();
		if(settings)
			settings->update();

		controls = settings->getControls();
		audio = settings->getAudio();
	}
	else if (exitGame)
	{
		if (!endgame)
			if (enemiesDead())
				endgame = new EndGame(0);
			else if (isDead() && playerInitialized)
				endgame = new EndGame(1);
			else 
				endgame = new EndGame(2);
		if(endgame)
			endgame->update();
	}
}

void Game::draw()
{
	graphics::Brush br;
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if(!startGame && !startSettings && !exitGame)
	{
		//draw ui
		br.texture = std::string(ASSET_PATH) + "space.png";
		br.outline_opacity = 0.0;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		br.texture = std::string(ASSET_PATH) + "logo.png";
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 3, 460, 194, br);

		br.texture = "";
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;

		graphics::drawText(CANVAS_WIDTH / 2 - 50, CANVAS_HEIGHT * 2 / 3, 20, "START GAME", br);
		graphics::drawText(CANVAS_WIDTH / 2 - 40, CANVAS_HEIGHT * 2 / 3 + 35, 20, "SETTINGS", br);
		graphics::drawText(CANVAS_WIDTH / 2 - 42, CANVAS_HEIGHT * 2 / 3 + 70, 20, "EXIT GAME", br);

		if (mouse.cur_pos_x >= 540 && mouse.cur_pos_x <= 670 && mouse.cur_pos_y >= 380 && mouse.cur_pos_y <= 400)
		{
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.25f;
			br.fill_color[2] = 0.1f;
			graphics::drawText(CANVAS_WIDTH / 2 - 50, CANVAS_HEIGHT * 2 / 3, 20, "START GAME", br);
		}
		else if (mouse.cur_pos_x >= 550 && mouse.cur_pos_x <= 650 && mouse.cur_pos_y >= 425 && mouse.cur_pos_y <= 440)
		{
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.25f;
			br.fill_color[2] = 0.1f;
			graphics::drawText(CANVAS_WIDTH / 2 - 40, CANVAS_HEIGHT * 2 / 3 + 35, 20, "SETTINGS", br);
		}
		else if (mouse.cur_pos_x >= 550 && mouse.cur_pos_x <= 650 && mouse.cur_pos_y >= 465 && mouse.cur_pos_y <= 485)
		{
			br.fill_color[0] = 1.0f;
			br.fill_color[1] = 0.25f;
			br.fill_color[2] = 0.1f;
			graphics::drawText(CANVAS_WIDTH / 2 - 42, CANVAS_HEIGHT * 2 / 3 + 70, 20, "EXIT GAME", br);
		}

		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::drawText(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 30 + 15, 12, "MOUSE: Select", br);
	}
	else if (startGame)
	{
		//draw background
		br.texture = std::string(ASSET_PATH) + "space.png";
		br.outline_opacity = 0.0;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		//draw score board
		br.texture = "";
		graphics::drawText(10, 24, 18, "SCORE", br);
		graphics::drawText(70, 24, 18, std::to_string(score), br);

		//draw lifes
		for (int i = 0; i < lifes; i++)
		{
			graphics::Brush brh;
			brh.texture = std::string(ASSET_PATH) + "heart.png";
			brh.outline_opacity = 0.0f;
			graphics::drawRect(CANVAS_WIDTH - 40 - i * 25, 25, 20, 20, brh);
		}

		//draw boarders
		if (getDebugMode())
		{
			graphics::Brush brDebug;
			brDebug.fill_color[0] = 1.0f;
			brDebug.fill_color[1] = 1.0f;
			brDebug.fill_color[2] = 1.0f;
			brDebug.fill_opacity = 0.3f;
			brDebug.outline_opacity = 0.0f;
			graphics::drawRect((RIGHT_BOARDER + CANVAS_WIDTH) / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH - RIGHT_BOARDER, CANVAS_HEIGHT, brDebug);
			graphics::drawRect(LEFT_BOARDER / 2, CANVAS_HEIGHT / 2, LEFT_BOARDER, CANVAS_HEIGHT, brDebug);
		}

		//draw game objects
		if (player)
			player->draw();

		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			if (enemies[i])
				enemies[i]->draw();

		if (explosion)
			explosion->draw();

		if (ufo)
			ufo->draw();

		for (int i = 0; i < SHIELD_NUM; i++)
			if (shields[i])
				shields[i]->draw();
	}
	else if (startSettings)
	{
		if (settings)
			settings->draw();
	}
	else if (exitGame)
	{
			if (endgame)
				endgame->draw();
	}	
}

void Game::init()
{
	//set font for game texts
	graphics::setFont(std::string(ASSET_PATH) + "BarlowSemiCondensed-Black.ttf");
	//enemy array and shield array initialize with nullptr
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
		enemies[i] = nullptr;

	for (int i = 0; i < SHIELD_NUM; i++)
		shields[i] = nullptr;
}

bool Game::enemiesDead()
{
	//check if all enemies are dead 
	//return true if alla are dead and false if not
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		if (enemies[i])
			return false;
	}
	return true && enemiesInitialized;
}

bool Game::isDead()
{
	//check if player has lifes
	if (lifes == 0)
		return true;
	else
		return false;
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
		delete player;
	
	if (enemiesInitialized)
		for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			delete enemies[i];

	if (explosion)
		delete explosion;

	if (ufo)
		delete ufo;

	if (settings)
		delete settings;

	if (endgame)
		delete endgame;

	if (shieldInitialized)
		for (int i = 0; i < SHIELD_NUM; i++)
			delete shields[i];
}