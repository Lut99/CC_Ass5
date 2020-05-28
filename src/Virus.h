#ifndef VIRUS_INCLUDED
#define VIRUS_INCLUDED

#include "MySDL.h"
#include "Coord.h"

/*! A Virus, be carefull
 */
class Virus
{
public:
    Virus()
    {}

    /*! Creates a Virus
      @param pos start position
      @param speed start speed
     */
    Virus(Coord pos,Coord speed) :
        pos{pos}, speed{speed}
    {}

    /*! Makes a step in time
      @param mySDL for the size of the window
     */
    void step(MySDL& mySDL)
    {
        pos+=speed;
        if (pos.x<0 || pos.x>mySDL.size().x)
        { speed.x=-speed.x; }
        if (pos.y<0 || pos.y>mySDL.size().y)
        { speed.y=-speed.y; }
    }
    
    /*! Draws the Virus
      @param mySDL for the size of the window
     */
    void draw(MySDL& mySDL)
    {
        filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0));
    }
    
private:
    static const int radius=10;
    Coord pos,speed;
};

#endif
