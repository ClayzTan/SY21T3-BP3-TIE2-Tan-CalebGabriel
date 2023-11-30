#include "Explosion.h"

void Explosion::start()
{
	// Load Texture
	texture = loadTexture("gfx/explosion.png");

	// Initialize to prevent junk
	x = 100;
	y = 100;

	// Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Explosion::update()
{
}

void Explosion::draw()
{
	blit(texture, x, y);
}

void Explosion::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
