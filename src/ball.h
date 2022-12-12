#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "Hole.h"
#include "Tile.h"

#include "entity.h"
#include "math.h"
#include "breaker.h"

class Ball : public Entity
{
public:
	Ball(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f& getVelocity()
	{
		return velocity;
	}
    Vector2f& getInitialMousePos()
	{
		return initialMousePos;
	}
    int getStrokes()
    {
        return strokes;
    }
    bool isWin()
    {
        return win;
    }
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void update(double deltaTime, bool &mousePressed, Breaker breaker, std::vector<Tile> tiles);
private:
    Vector2f velocity;
    Vector2f target;
    Vector2f launchedVelocity;
    float velocity1D;
    float launchedVelocity1D;
    float newX;
    float newY;
    Vector2f initialMousePos;
    bool canMove = true;
    bool playedSwingFx = true;
    int index;
    int strokes = 0;
    int dirX = 1;
    int dirY = 1;
    bool win = false;
};