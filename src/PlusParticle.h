/* PLUS PARTICLE.h
 *   by Anonymous
 *
 * Created:
 *   5/28/2020, 10:21:54 PM
 * Last edited:
 *   5/28/2020, 11:59:59 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This class implements a Plus-particle: little green objects in a plus
 *   shape. Used by the good virusses.
**/

#ifndef PLUSPARTICLE_INCLUDED
#define PLUSPARTICLE_INCLUDED

#include "Particle.h"

class PlusParticle: public Particle {
    public:
        /*! Creates a new PlusParticle object with Random position and speed
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        PlusParticle(double size = 2.5, unsigned int lifetime = 60)
            : Particle(ParticleType::plus, size, lifetime)
        {}

        /*! Creates a new PlusParticle object with a given position but a random speed.
          @param position set the starting position of the PlusParticle
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        PlusParticle(Coord pos, double size = 2.5, unsigned int lifetime = 60)
            : Particle(pos, ParticleType::plus, size, lifetime)
        {}

        /*! Creates a new PlusParticle object with a given position and a given speed.
          @param position the starting position of the PlusParticle
          @param speed the starting speed (and direction) of the PlusParticle
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        PlusParticle(Coord pos, Coord speed, double size = 2.5, unsigned int lifetime = 60)
            : Particle(pos, speed, ParticleType::plus, size, lifetime)
        {}

        /*! Draws the particle
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Set the render colour
            SDL_SetRenderDrawColor(mySDL.renderer(), 0, 255 * (this->lifetime / this->duration), 0, 255);
            
            // Horizontal line
            SDL_RenderDrawLine(mySDL.renderer(), this->pos.x - this->size, this->pos.y, this->pos.x + this->size, this->pos.y);

            // Vertical line
            SDL_RenderDrawLine(mySDL.renderer(), this->pos.x, this->pos.y - this->size, this->pos.x, this->pos.y + this->size);
        }
};

#endif
