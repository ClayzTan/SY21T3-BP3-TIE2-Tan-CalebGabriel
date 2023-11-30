#include "Background.h"

void Background::start()
{
	// Load Texture
	texture = loadTexture("gfx/background.png");

	// Initialize to prevent junk
	x = 0;
	y = 0;
	width = 100;
	height = 100;

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blitScale(texture, 0, 0, &width, &height, 3);
}

void Background::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
