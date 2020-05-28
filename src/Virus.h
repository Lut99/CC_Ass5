#ifndef VIRUS_INCLUDED
#define VIRUS_INCLUDED

#include "MySDL.h"
#include "Coord.h"
#include "Unit.h"

/*! A Virus, be carefull
 */
class Virus: public Unit
{
public:
    /*! Creates a Virus with default position and speed
     */
    Virus() :
        Unit(10)
    {}

    /*! Creates a Virus
      @param pos start position
      @param speed start speed
     */
    Virus(Coord pos,Coord speed) :
        Unit(pos, speed, 10)
    {}

    /*! Allows the Virus to handle keyboardinputs, but does nothing as the Virus does not do this
      @param keyboardState the current state (keys pressed) of the keyboard
     */
    virtual void keyboard(const Uint8* keyboardState)
    {}
    
    /*! Draws the Virus
      @param mySDL for the size of the window
     */
    virtual void draw(MySDL& mySDL)
    {
        filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0));
    }
};

#endif
