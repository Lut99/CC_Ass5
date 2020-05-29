/* END TEXT.h
 *   by Anonymous
 *
 * Created:
 *   5/29/2020, 4:24:37 PM
 * Last edited:
 *   5/29/2020, 5:15:13 PM
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

class EndText: public Text {
    private:
        std::string msg;
        Color colour;
        double alpha;
        double colour_speed;
        bool alpha_up;

    public:
        /*! Creates a new FlavourText object with default position.
          @param mySDL the window to render on
          @param won if set to true, displays 'You won!'; otherwise, displayes 'You lost...'
         */
        EndText(MySDL& mySDL, bool won)
            : Text(
                mySDL,
                Coord(mySDL.size().x / 2, mySDL.size().y / 2),
                "",
                "../Raleway-Regular.ttf",
                72,
                color(0, 0, 0, 0)),
            msg(won ? "You won!!!" : "You lost..."),
            colour(won ? color(245, 155, 0) : color(86, 0, 245)),
            alpha(0),
            colour_speed(.25),
            alpha_up(true)
        {}

        /*! Updates the flavourtext, i.e., decreases it's lifetime and floats it up
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            // Fetch the colour as lsit
            Uint8* c_list = (Uint8*) &(this->colour);

            Uint8 r = c_list[0] * (this->alpha / 255);
            Uint8 g = c_list[1] * (this->alpha / 255);
            Uint8 b = c_list[2] * (this->alpha / 255);

            // Create a new render with that colour
            this->initialize_texture(mySDL, this->msg, color(r, g, b));

            // Update the alpha
            if (alpha_up) {
                this->alpha += this->colour_speed;
                if (this->alpha >= 255.0) {
                    this->alpha = 255.0;
                    this->alpha_up = false;
                }
            } else {
                this->alpha -= this->colour_speed;
                if (this->alpha <= 0.0) {
                    this->alpha = 0.0;
                    this->alpha_up = true;
                }
            }
        }
};

#endif
