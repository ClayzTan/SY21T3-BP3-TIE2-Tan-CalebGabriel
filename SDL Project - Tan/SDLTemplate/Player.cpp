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
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8;
	currentReloadTime = 0;
	reloadTime2 = 16;
	currentReloadTime2 = 0;

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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
		Bullet* bullet = new Bullet(x + width, y - 4 + height / 2, 1, 0, 10);
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
		Bullet* bullet1 = new Bullet(x + width, y - 6 + height, 1, 0, 10);
		bullets.push_back(bullet1);
		getScene()->addGameObject(bullet1);
		bullet1->start();
		Bullet* bullet2 = new Bullet(x + width, y - 26 + height / 2, 1, 0, 10);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet2);
		bullet2->start();

		// Reset reload time after firing
		currentReloadTime2 = reloadTime2;
	}
	
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
}

void Player::draw()
{
	blit(texture, x, y);
}
