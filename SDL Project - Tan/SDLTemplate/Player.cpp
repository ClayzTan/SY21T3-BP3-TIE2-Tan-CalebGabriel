#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// Memory manage bullets, delete on death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	// Load texture
	texture = loadTexture("gfx/player.png");

	// Initialize to prevent junk
	x = 600;
	y = 600;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8;
	currentReloadTime = 0;
	reloadTime2 = 16;
	currentReloadTime2 = 0;
	isAlive = true;

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	// Memory manage bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			// Cache variable to delete later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + 35 - width / 2, y + 35 - height, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		// Reset reload time after firing
		currentReloadTime = reloadTime;
	}

	if (currentReloadTime2 > 0)
		currentReloadTime2--;

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime2 == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet1 = new Bullet(x + 10 - width / 2, y + 35 - height, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		Bullet* bullet2 = new Bullet(x + 55 - width / 2, y + 35 - height, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);

		// Reset reload time after firing
		currentReloadTime2 = reloadTime2;
	}
}

void Player::draw()
{
	if (!isAlive) return;
	//blit(texture, x, y);
	blitRotate(texture, x, y, 270);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::death()
{
	isAlive = false;
}
