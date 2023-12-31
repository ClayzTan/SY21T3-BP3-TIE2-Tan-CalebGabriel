#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Explosion.h"
#include "Background.h"
#include "PowerUp.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Background* background;
	Explosion* explosion;

	// Enemy Spawn Logic
	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	float spawnTime2;
	float currentSpawnTimer2;
	std::vector<PowerUp*> spawnedPowerUps;

	void spawnLogic();
	void collisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);
	void spawnPowerUp();
	void despawnPowerUp(PowerUp* powerup);

	int points;
};

