#pragma once
#include "graphics.h"
#include "config.h"
#include "Player.h"
#include "enemy.h"
#include "explosion.h"
#include "ufo.h"
#include "endgame.h"
#include "settings.h"
#include "shield.h"

class Game
{
	bool closeApplication = false;

	Settings* settings = nullptr;
	EndGame* endgame = nullptr;
	int choise = 1;
	bool startGame = false, startSettings = false, exitGame = false;
	bool controls = true, audio = true;

	int score = 0, lifes = 3;
	bool debug_mode = false;

	bool playerInitialized = false, enemiesInitialized = false, ufoInitialized = false;
	Player* player = nullptr;
	Enemy* enemies[NUMBER_OF_ENEMIES];
	Ufo* ufo = nullptr;
	Explosion* explosion;
	float timeCreate;
	Shield* shields[SHIELD_NUM];
	bool shieldInitialized = false;

	void spawnEnemy();
	void spawnShield();
	void checkUfo();

	void collisionDetectionForEnemy();
	void collisionDetectionForPlayer();
	void collisionDetectionForBullets();
	void collisionDetectionForEnemyPlayer();
	void collisionDetectionForUfo();
	void collisionDetectionForShieldEnemy();
	void collisionDetectionForShieldPlayer();
	void createExplosionEnemy(int i);
	void createExplosionPlayer();
	void createExplosionBullet();
	void createExplosionUfo();
	void refreshMenuChoise();
	void restartGame();
	
	bool enemiesDead();
	bool isDead();

public:
	Game();
	~Game();
	void update();
	void draw();
	void init();

	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	Enemy* getEnemy(int i) const { return enemies[i]; }
	bool getControls() const{ return controls; }
	bool getAudio() const{ return audio; }
	bool getCloseApplication() const { return closeApplication; }
};