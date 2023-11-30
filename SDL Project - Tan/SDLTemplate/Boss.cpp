#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	// Load texture
	texture = loadTexture("gfx/enemy.png");

	// Initialize to prevent junk
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 1;
	reloadTime = 60; // Reload time of 60 frames = 1 second
	currentReloadTime = 0;
	directionChangeTime = (rand() % 120) + 120; // Direction change time
	currentDirectionChangeTime = 0;

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionX = -directionX;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		//calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 9 - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x - 6 - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x - 3 -width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x + 3 - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x + 6 - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		Bullet* bullet = new Bullet(x + 9 - width / 2, y - 4 + height, 0, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// Reset reload time after firing
		currentReloadTime = reloadTime;
	}

	// Memory manage bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache variable to delete later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blitScale(texture, x, y, 2);
	blitRotate(texture, x, y, 270);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
