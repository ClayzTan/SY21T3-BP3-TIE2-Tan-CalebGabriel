#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new Background();
	this->addGameObject(background);

	player = new Player();
	this->addGameObject(player);

	explosion = new Explosion();

	points = 0;
}

GameScene::~GameScene()
{
	delete player;

	delete explosion;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300; // 5 second Spawn time

	currentSpawnTimer2 = 480;
	spawnTime2 = 480;

	for (int i = 0; i < 3; i++)
	{
		spawn();
	}

	for (int i = 0; i < 1; i++)
	{
		spawnPowerUp();
	}
}

void GameScene::draw()
{
	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	Scene::update();
	spawnLogic();
	collisionLogic();	
}

void GameScene::spawnLogic()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
		}

		currentSpawnTimer = spawnTime;
	}

	if (currentSpawnTimer2 > 0)
		currentSpawnTimer2--;

	if (currentSpawnTimer2 <= 0)
	{
		for (int i = 0; i < 1; i++)
		{
			spawnPowerUp();
		}

		currentSpawnTimer2 = spawnTime2;
	}


}

void GameScene::collisionLogic()
{
	// Main Collision Logic Code
	for (int i = 0; i < objects.size(); i++)
	{
		// Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		// Check if cast was successful
		if (bullet != NULL)
		{
			// If bullet from enemy side chek against the player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->death();
					break;
				}
			}
			// If bullet from player side, check against all enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						despawnEnemy(currentEnemy);
						// Increment Points
						this->addGameObject(explosion);
						explosion->setPosition(currentEnemy->getPositionX(), currentEnemy->getPositionY());
						points++;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < objects.size(); i++)
	{
		// Cast to powerup
		PowerUp* powerup = dynamic_cast<PowerUp*>(objects[i]);

		// Check if cast was successful
		if (powerup != NULL)
		{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					PowerUp* currentPowerUp = spawnedPowerUps[i];

					int collision = checkCollision(
						currentPowerUp->getPositionX(), currentPowerUp->getPositionY(), currentPowerUp->getWidth(), currentPowerUp->getHeight(),
						player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight()
					);

					if (collision == 1)
					{
						despawnPowerUp(currentPowerUp);
						// Increment Points
						
						break;
					}
				}
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition((rand() % 300) + 300, -600);
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// If the pointer matches
		if (enemy = spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	// If any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::spawnPowerUp()
{
	PowerUp* powerup = new PowerUp();
	this->addGameObject(powerup);

	powerup->setPosition((rand() % 300) + 300, -600);
	spawnedPowerUps.push_back(powerup);
}

void GameScene::despawnPowerUp(PowerUp* powerup)
{
	int index = -1;
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		// If the pointer matches
		if (powerup = spawnedPowerUps[i])
		{
			index = i;
			break;
		}
	}

	// If any match is found
	if (index != -1)
	{
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete powerup;
	}
}
