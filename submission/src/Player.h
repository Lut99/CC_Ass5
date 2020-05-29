#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <string>

#include "Unit.h"
#include "MySDL.h"
#include "Coord.h"
#include "FlavourText.h"

/*! The object representing the player in VirusGame
 */
class Player: public Unit
{
    private:
        /*! The charge level of the player's inner colour. If that reaches 1, he wins the game!
         */
        int charge;
        /*! The amount of charge the player obtains when eating a good virus
         */
        int charge_add;
        /*! The amount of charge the player loses when eating an evil virus
         */
        int charge_min;

    public:
        /*! Creates the Player. Note that it lives on layer 10, and is only really supposed to be overwritten by text and fireworks.
          @param pos start position
        */
        Player(Coord pos, int good_charge = 0.05, int evil_charge = 0.15) :
            Unit(pos, Coord(0, 0), UnitType::player, 10),
            charge(0.0),
            charge_add(good_charge),
            charge_min(evil_charge)
        {}

        /*! Updates the gameobject. Particularly, it allows the object to do
            something on a keypress, when it touches the walls of the screen
            or when it touches another object.
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8* keyboardState, GameState& objects) {
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

            // Apply the computed speed
            pos+=speed;

            // Bounce off the sides, and make sure we stay within the sides
            if (pos.x < this->radius) {
                speed.x=-speed.x;
                pos.x = this->radius;
            } else if (pos.x > mySDL.size().x - this->radius) {
                speed.x = -speed.x;
                pos.x = mySDL.size().x - this->radius;
            }
            if (pos.y < this->radius) {
                speed.y=-speed.y;
                pos.y = this->radius;
            } else if (pos.y > mySDL.size().y - this->radius) {
                speed.y = -speed.y;
                pos.y = mySDL.size().y - this->radius;
            }

            // Eat other units
            for (auto& obj : objects.get_objects()) {
                // Skip all non-unit, non-virus objects
                if (this == obj || obj->type != GameObjectType::unit) { continue; }

                // Cast to unit

                // For all virus objects, check if we hit 'em
                Unit* unit = (Unit*) obj;
                if (this->distance_to(*unit) <= this->radius + unit->radius) {
                    // Either get points or lose 'em
                    if (unit->unit_type == UnitType::virus) {
                        this->charge += this->charge_add;
                    } else if (unit->unit_type == UnitType::evil_virus) {
                        this->charge += -this->charge_min;
                    }

                    // Either case, remove the virus as we ate it
                    objects.despawn(unit);

                    // Show a popup that displays this change
                    std::string to_disp = std::to_string(this->charge);
                    if (this->charge >= 0) {
                        to_disp += "/100";
                    } else {
                        to_disp += "/-100";
                    }

                    // Keep charge in 100
                    if (this->charge > 100) { this->charge = 100; }
                    else if (this->charge < -100) { this->charge = -100; }

                    // Spawn such an object
                    objects.spawn((GameObject*) new FlavourText(mySDL, this->pos, to_disp));
                }
            }
        }

        /*! Draws the Player
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Chose the color based on the charge
            Color c;
            if (charge >= 0) {
                c = color(0, 255 * (this->charge / 100.0), 0);
            } else {
                c = color(255 * (-this->charge / 100.0), 0, 0);
            }

            // Draw the player
            filledCircleColor(mySDL.renderer(), this->pos.x, this->pos.y, this->radius, c);
            aacircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,255,255));
        }

        /*! Returns the charge the player has collected
         */
        int get_charge() const {
            return this->charge;
        }
};

#endif
