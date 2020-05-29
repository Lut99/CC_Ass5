/* END TEXT.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/29/2020, 4:24:37 PM
 * Last edited:
 *   5/29/2020, 11:07:36 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The EndText class is used to display a large victory or lose text on
 *   the screen. Additionally, it changes it's colours according to a
 *   matching colour scheme.
**/

#ifndef ENDTEXT_INCLUDED
#define ENDTEXT_INCLUDED

#include <string>

#include "Text.h"
#include "MySDL.h"

class EndText: public Text {
    private:
        std::string msg;
        SDL_Color colour;
        double alpha;
        bool alpha_up;


        const double colour_speed = 2;

    public:
        /*! Creates a new FlavourText object with default position.
          @param mySDL the window to render on
          @param won if set to true, displays 'You won!'; otherwise, displayes 'You lost...'
         */
        EndText(MySDL& mySDL, bool won)
            : Text(
                mySDL,
                Coord(mySDL.size().x / 2, mySDL.size().y / 2),
                "PLACEHOLDER",
                "../Raleway-Regular.ttf",
                72,
                SDL_Color({0, 0, 0})),
            msg(won ? "You won!!!" : "You lost..."),
            colour(won ? SDL_Color({245, 155, 0}) : SDL_Color({86, 0, 245})),
            alpha(0),
            alpha_up(true)
        {}

        /*! Updates the flavourtext, i.e., decreases it's lifetime and floats it up
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            // Bring the text in as long as we still have alpha to go
            if (alpha_up) {
                // Update the alpha in the stored colour
                SDL_Color alpha_colour(this->colour);
                alpha_colour.r *= this->alpha / 255.0;
                alpha_colour.g *= this->alpha / 255.0;
                alpha_colour.b *= this->alpha / 255.0;

                // Create a new render with that colour
                this->initialize_texture(mySDL, this->msg, alpha_colour);

                // Update the alpha
                this->alpha += this->colour_speed;
                if (this->alpha > 255.0) {
                    this->alpha = 255.0;
                    this->alpha_up = false;
                }
            }
        }
};

#endif
