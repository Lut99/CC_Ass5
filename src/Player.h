#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Unit.h"
#include "MySDL.h"
#include "Coord.h"

/*! The object representing the player in VirusGame
 */
class Player: public Unit
{
public:
    /*! Creates the Player. Sets the speed to zero
      @param pos start position
     */
    Player(Coord pos) :
        Unit(pos, Coord(0, 0), 24)
    {}

    /*! Handles the keyboard events
      @param keyboardState the current state (keys pressed) of the keyboard
     */
    virtual void keyboard(const Uint8* keyboardState)
    {
        double diff_speed=0.5;
        // for others keys see: https://wiki.libsdl.org/SDL_Scancode
        if (keyboardState[SDL_SCANCODE_UP])
            speed.y-=diff_speed;
        if (keyboardState[SDL_SCANCODE_DOWN])
            speed.y+=diff_speed;
        if (keyboardState[SDL_SCANCODE_LEFT])
            speed.x-=diff_speed;
        if (keyboardState[SDL_SCANCODE_RIGHT])
            speed.x+=diff_speed;
        // if (keyboardState[SDL_SCANCODE_A])
        speed*=0.95; // reduce speed to create some resistance
    }

    /*! Draws the Player
      @param mySDL for the size of the window
     */
    virtual void draw(MySDL& mySDL)
    {   aacircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,255,255)); }
};

#endif
