#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class PowerUp :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    void setPosition(int x, int y);
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
    int speed;
    float directionX;
    float directionY;
    float directionChangeTime;
    float currentDirectionChangeTime;
};

