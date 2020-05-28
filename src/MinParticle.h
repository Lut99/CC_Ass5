/* MIN PARTICLE.h
 *   by Anonymous
 *
 * Created:
 *   5/28/2020, 11:59:00 PM
 * Last edited:
 *   5/29/2020, 1:15:01 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   A particle that display little, red minusses. Used by the evil
 *   virusses.
**/

#ifndef MINPARTICLE_INCLUDED
#define MINPARTICLE_INCLUDED

#include "Particle.h"

class MinParticle: public Particle {
    public:
        /*! Creates a new MinParticle object with Random position and speed
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        MinParticle(double size = 2.5, unsigned int lifetime = 60)
            : Particle(ParticleType::min, size, lifetime)
        {}

        /*! Creates a new MinParticle object with a given position but a random speed.
          @param position set the starting position of the MinParticle
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        MinParticle(Coord pos, double size = 2.5, unsigned int lifetime = 60)
            : Particle(pos, ParticleType::min, size, lifetime)
        {}

        /*! Creates a new MinParticle object with a given position and a given speed.
          @param position the starting position of the MinParticle
          @param speed the starting speed (and direction) of the MinParticle
          @param size overrides the default size of the particle
          @param lifetime overrides the default number of frames that the particle is alive
         */
        MinParticle(Coord pos, Coord speed, double size = 2.5, unsigned int lifetime = 60)
            : Particle(pos, speed, ParticleType::min, size, lifetime)
        {}

        /*! Draws the particle
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Set the render colour
            SDL_SetRenderDrawColor(mySDL.renderer(), 255 * (this->lifetime / this->duration), 0, 0, 255);
            
            // Horizontal line
            SDL_RenderDrawLine(mySDL.renderer(), this->pos.x - this->size, this->pos.y, this->pos.x + this->size, this->pos.y);
        }
};

#endif
