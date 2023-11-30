#include "PowerUp.h"
#include "Scene.h"

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");

	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 3;
	directionChangeTime = (rand() % 120) + 60; // Direction change time
	currentDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
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
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}

void PowerUp::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
