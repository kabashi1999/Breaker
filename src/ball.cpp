#include "ball.h"
#include "entity.h"
#include "math.h"
#include "tile.h"
#include "breaker.h"


#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


Ball::Ball(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{
  
}

void Ball::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}


void Ball::setWin(bool p_win)
{
    win = p_win;
}

void Ball::update(double deltaTime, bool &mousePressed, Breaker breaker, std::vector<Tile> tiles)
{   
    if (win)
    {
        if (getPos().x < target.x)
        {
            setPos(getPos().x += 0.1*deltaTime, getPos().y);
        }
        else if (getPos().x > target.x)
        {
            setPos(getPos().x -= 0.1*deltaTime, getPos().y);
        }
        if (getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y += 0.1*deltaTime);
        }
        else if (getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y -= 0.1*deltaTime);
        }
        setScale(getScale().x - 0.001*deltaTime, getScale().y - 0.001*deltaTime);
        return;
    }
    
    if (mousePressed)
    {
        
        int mouseX = 0;
	    int mouseY = 0;
	    SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity(100/-150, 100/-150);
        setLaunchedVelocity(100/-150, 100/-150);
        velocity1D = SDL_sqrt(SDL_pow(abs(getVelocity().x), 2) + SDL_pow(abs(getVelocity().y), 2));
        launchedVelocity1D = velocity1D;
 

        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);

    
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
      mousePressed = false;
    }
    else
    {
       
 
        canMove = false;
        setPos(getPos().x + getVelocity().x*deltaTime, getPos().y + getVelocity().y*deltaTime);
   
      //bounce of walls

        if (getPos().x + getCurrentFrame().w > 640)
        {
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0)
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getCurrentFrame().h > 640)
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        else if (getPos().y < 0)
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }
      //bounce of tiles

        for (Tile& t : tiles)
	    { 
		     newX = getPos().x + getVelocity().x*deltaTime;
             newY = getPos().y;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;
            }

            newX = getPos().x;
            newY = getPos().y + getVelocity().y*deltaTime;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
	    }
      //bounce of the breaker
      		 newX = getPos().x + getVelocity().x*deltaTime;
             newY = getPos().y;
            if (newX + 16 > breaker.getPos().x && newX < breaker.getPos().x + breaker.getCurrentFrame().w && newY + 16 > breaker.getPos().y && newY < breaker.getPos().y + breaker.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x*-1, getVelocity().y);
                dirX *= -1;
            }

            newX = getPos().x;
            newY = getPos().y + getVelocity().y*deltaTime;
            if (newX + 16 > breaker.getPos().x && newX < breaker.getPos().x + breaker.getCurrentFrame().w && newY + 16 > breaker.getPos().y && newY < breaker.getPos().y + breaker.getCurrentFrame().h - 3)
            {
                setVelocity(getVelocity().x, getVelocity().y*-1);
                dirY *= -1;
            }
      	
    }
    
}