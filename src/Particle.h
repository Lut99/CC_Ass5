/* PARTICLE.h
 *   by Anonymous
 *
 * Created:
 *   5/28/2020, 10:15:23 PM
 * Last edited:
 *   5/29/2020, 1:31:00 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Particle class forms the baseclass of all particles - i.e.,
 *   non-interactable, fleeting and small objects.
**/

#ifndef PARTICLE_INCLUDED
#define PARTICLE_INCLUDED

#include "GameObject.h"
#include "Coord.h"

/*! Lists all the possible particle types
 */
enum class ParticleType {
    fireworks,
    plus,
    min
};

/*! A class for small, fleeting and non-interactable objects.
 */
class Particle: public GameObject {
    protected:
        Coord speed;
        double size;
        unsigned int lifetime;
        double duration;

        /*! Creates a new particle object with a random speed and random position.
          @param type the type of the new particle
          @param size the width == height of the particle, in pixels
          @param lifetime the number of frames the particle gets to live
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        Particle(ParticleType type, double size, unsigned int lifetime = 0)
            : GameObject(GameObjectType::particle, layer),
            size(size),
            lifetime(lifetime),
            duration(lifetime),
            particle_type(type)
        {}

        /*! Creates a new particle object with a random speed but a given position.
          @param position the position of the new particle
          @param type the type of the new particle
          @param size the width == height of the particle, in pixels
          @param lifetime the number of frames the particle gets to live
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        Particle(Coord position, ParticleType type, double size, unsigned int lifetime, unsigned int layer = 0)
            : GameObject(position, GameObjectType::particle, layer),
            size(size),
            lifetime(lifetime),
            duration(lifetime),
            particle_type(type)
        {}

        /*! Creates a new particle object with a random speed but a given position.
          @param position the position of the new particle
          @param speed the speed (and therefore direction) of the new particle
          @param type the type of the new particle
          @param size the width == height of the particle, in pixels
          @param lifetime the number of frames the particle gets to live
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        Particle(Coord position, Coord speed, ParticleType type, double size, unsigned int lifetime, unsigned int layer = 0)
            : GameObject(position, GameObjectType::particle, layer),
            speed(speed),
            size(size),
            lifetime(lifetime),
            duration(lifetime),
            particle_type(type)
        {}
    
    public:
        const ParticleType particle_type;

        /*! Updates the particle. This is just moving it around with it's speed
            and decreasing it's lifetime gradually (so it lives about a second).
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
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
};

#endif
