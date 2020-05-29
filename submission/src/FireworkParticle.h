/* FIREWORK PARTICLE.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/29/2020, 8:53:25 PM
 * Last edited:
 *   5/29/2020, 11:07:37 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Updates and draws a firework particle
**/

#ifndef FIREWORKPARTICLE_INCLUDED
#define FIREWORKPARTICLE_INCLUDED

#include "Particle.h"
#include "Utils.h"

class FireworkParticle: public Particle {
    private:
        SDL_Color colour;

    public:
        /*! Creates a new FireworkParticle object with given position and direction
          @param position the starting position of the particle
          @param direction the direction of the particle (normalized speed vector)
          @param colour the colour of this particle
          @param size the size of the particle
          @param lifetime the lifetime (in frames) of this particle
         */
        FireworkParticle(Coord position, Coord direction, SDL_Color colour, double size = 2.5, unsigned int lifetime = 60)
            : Particle(position, direction * (rand_0_1() * 2 + 10), ParticleType::fireworks, size, lifetime, 25),
            colour(colour)
        {}

        /*! Updates the particle. Aside from just moving it around with it's speed
            and decreasing it's lifetime gradually (so it lives about a second), it also applies
            a lot of drag and a bit of gravity.
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            // Apply the drag and the gravity to the speed
            this->speed.x *= 0.95;
            this->speed.y = this->speed.y * 0.95 + 0.25;

            // Apply the internal speed
            this->pos += this->speed;
            if (this->pos.x<0 || this->pos.x>mySDL.size().x)
            { this->speed.x=-this->speed.x; }
            if (this->pos.y<0 || this->pos.y>mySDL.size().y)
            { this->speed.y=-this->speed.y; }

            // Decrease the lifetime
            this->lifetime--;
            if (lifetime == 0) {
                // Lifetime over...
                objects.despawn(this);
            }
        }

        /*! Draws the particle
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Reduce the inner colour with the lifetime
            int r = this->colour.r * (this->lifetime / this->duration);
            int g = this->colour.g * (this->lifetime / this->duration);
            int b = this->colour.b * (this->lifetime / this->duration);

            // Draw the circle
            filledCircleRGBA(mySDL.renderer(), this->pos.x, this->pos.y, this->size, r, g, b, 255);
        }
};

#endif
