#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Explosion :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    void setPosition(int x, int y);
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
};

