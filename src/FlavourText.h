/* FLAVOUR TEXT.h
 *   by Anonymous
 *
 * Created:
 *   5/29/2020, 3:27:27 PM
 * Last edited:
 *   5/29/2020, 4:25:58 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This text defines small, floating texts that dissappear soon, just to
 *   add something to the game.
**/

#ifndef FLAVOURTEXT_INCLUDED
#define FLAVOURTEXT_INCLUDED

#include <string>

#include "Text.h"

class FlavourText: public Text {
    private:
        double speed;
        unsigned int lifetime;

    public:
        /*! Creates a new FlavourText object with default position.
          @param mySDL the window to render on
          @param message the message which the flavourtext displays.
          @param speed the speed by which it floats up
          @param lifetime the number of frames it takes before dissappearing altogether
         */
        FlavourText(MySDL& mySDL, std::string message, double speed = 2.5, unsigned int lifetime = 45)
            : Text(mySDL, message, "../Raleway-Regular.ttf", 24, color(255, 255, 255)),
            speed(speed),
            lifetime(lifetime)
        {}

        /*! Creates a new FlavourText object with given position.
          @param mySDL the window to render on
          @param position the given position of the flavourtext
          @param message the message which the flavourtext displays.
          @param speed the speed by which it floats up
          @param lifetime the number of frames it takes before dissappearing altogether
         */
        FlavourText(MySDL& mySDL, Coord position, std::string message, double speed = 2.5, unsigned int lifetime = 45)
            : Text(mySDL, position, message, "../Raleway-Regular.ttf", 24, color(255, 255, 255)),
            speed(speed),
            lifetime(lifetime)
        {}

        /*! Updates the flavourtext, i.e., decreases it's lifetime and floats it up
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            // Apply the internal speed
            this->pos.y -= this->speed;

            // Decrease the lifetime
            this->lifetime--;
            if (lifetime == 0) {
                // Lifetime over...
                objects.despawn(this);
            }
        }
};

#endif
