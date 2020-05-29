/* RAIN PARTICLE.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/29/2020, 9:28:25 PM
 * Last edited:
 *   5/29/2020, 11:07:37 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   A particle that somewhat resembles rain. Is just a blue line that
 *   falls down with an angle of straight down or slightly to the right. 
**/

#ifndef RAINPARTICLE_INCLUDED
#define RAINPARTICLE_INCLUDED

#include "Particle.h"
#include "Utils.h"

class RainParticle: public Particle {
    public:
        /*! Creates a new FireworkParticle object with given position and direction
          @param position the starting position of the particle, probably somewhere above the screen
          @param direction the direction of the particle (normalized speed vector)
         */
        RainParticle(Coord position, Coord direction)
            : Particle(position, direction * (rand_0_1() * 2 + 4), ParticleType::fireworks, 0, 0, 25)
        {}

        /*! Updates the particle. For the rain, this is just moving around with it's speed
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8* keyboardState, GameState& objects) {
            // Apply the internal speed
            this->pos += this->speed;

            // Despawn the particle if it falls off the bottom of the screen
            if (this->pos.y > mySDL.size().y) {
                objects.despawn(this);
            }
        }

        /*! Draws the particle
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Set the render colour
            SDL_SetRenderDrawColor(mySDL.renderer(), 34, 171, 240, 255);
            
            // Draw the rain line
            double xspeed = this->speed.x;
            double yspeed = this->speed.y;
            SDL_RenderDrawLine(mySDL.renderer(), this->pos.x - xspeed, this->pos.y - yspeed, this->pos.x + xspeed, this->pos.y + yspeed);
        }
        
};

#endif
