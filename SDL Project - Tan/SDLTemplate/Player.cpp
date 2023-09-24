#include "Player.h"

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

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
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
}

void Player::draw()
{
	blit(texture, x, y);
}
