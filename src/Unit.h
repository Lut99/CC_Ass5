/* UNIT.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *
 * Created:
 *   5/28/2020, 4:41:23 PM
 * Last edited:
 *   5/28/2020, 5:02:18 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Unit class forms the baseclass of both the Virus and Human
 *   classes
**/

#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED

#include "MySDL.h"
#include "Coord.h"

/*! Baseclass for both Virusses and Players.
 */
class Unit {
    protected:
        const int radius;
        Coord pos;
        Coord speed;

        /*! Creates the unit with the default Coord values. Only the radius needs to be specified.
          @param radius the radius of the unit
         */
        Unit(const int radius)
          : radius(radius)
        {}
      
        /*! Creates the unit with the given values.
          @param position the initial position of the agent
          @param speed the initial speed (which incorporates direction) of the unit
          @param radius the radius of the unit
         */
        Unit(Coord position, Coord speed, const int radius)
            : pos(position),
            speed(speed),
            radius(radius)
        {}

    public:
        /*! Makes a step in time
          @param mySDL for the size of the window
         */
        virtual void step(MySDL& mySDL)
        {
            pos+=speed;
            if (pos.x<0 || pos.x>mySDL.size().x)
            { speed.x=-speed.x; }
            if (pos.y<0 || pos.y>mySDL.size().y)
            { speed.y=-speed.y; }
        }

        /*! Allows the unit to draw itself
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) = 0;

        /*! Allows the unit to handle keyboard events
          @param keyboardState the current state (keys pressed) of the keyboard
        */
        virtual void keyboard(const Uint8* keyboardState) = 0;
};

#endif
