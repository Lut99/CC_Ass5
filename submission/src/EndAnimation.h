/* END ANIMATION.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/29/2020, 8:44:05 PM
 * Last edited:
 *   5/29/2020, 11:07:36 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This game object is used as a generator for the end animation
 *   particles: fireworks on a win, rain on a loss
**/

#ifndef ENDANIMATION_INCLUDED
#define ENDANIMATION_INCLUDED

#include <cmath>

#include "GameObject.h"
#include "Utils.h"
#include "FireworkParticle.h"
#include "RainParticle.h"

class EndAnimation: public GameObject {
    protected:
        bool won;

        static constexpr double firework_chance = 0.05;
        static constexpr int firework_particles = 20;

        static constexpr double rain_chance = 0.5;

    public:
        /*! Creates the animation generator.
          @param won if set to true, displays the win animation; otherwise, it's the lose animation
         */
        EndAnimation(bool won)
            : GameObject(GameObjectType::end_animation, layer = 15),
            won(won)
        {}

        /*! Possibly generates the particles for the animation.
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8* keyboardState, GameState& objects) {
            if (won && rand_0_1() < this->firework_chance) {
                // Choose a random location on the screen (but let's say 25 from the border off)
                Coord pos(rand_0_1() * (mySDL.size().x - 50) + 25, rand_0_1() * (mySDL.size().y - 50) + 25);
                // Also generate a random colour for this bang
                SDL_Color colour({
                    (Uint8) (rand_0_1() * 255.0),
                    (Uint8) (rand_0_1() * 255.0),
                    (Uint8) (rand_0_1() * 255.0)
                });
                
                // Generate particles which launch in a random direction
                for (int i = 0; i < this->firework_particles; i++) {
                    // Create the normalized direction
                    Coord direction(rand_0_1() * 2 - 1, rand_0_1() * 2 - 1);
                    double direction_len = sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction.x /= direction_len;
                    direction.y /= direction_len;

                    // Create a particle as such
                    objects.spawn((GameObject*) new FireworkParticle(pos, direction, colour));
                }
            } else if (!won && rand_0_1() < this->rain_chance) {
                // Choose a random location above the screen
                Coord pos(rand_0_1() * mySDL.size().x, -50);

                // Choose a random direction between -3/8 and -4/8 pi radians
                double random_angle = (rand_0_1() - 4) / 8 * M_PI;
                Coord direction(cos(random_angle), -sin(random_angle));

                // Spawn a particle with that position and angle
                objects.spawn((GameObject*) new RainParticle(pos, direction));
            }
        }

        /*! Does nothing, as there is nothing of this object to draw
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const
        {}
};

#endif
