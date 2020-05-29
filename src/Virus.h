#ifndef VIRUS_INCLUDED
#define VIRUS_INCLUDED

#include <iostream>
#include <cmath>

#include "MySDL.h"
#include "Utils.h"
#include "Coord.h"
#include "Unit.h"
#include "PlusParticle.h"

static const unsigned int particle_interval = 5;

/*! A Virus, try to eat it !
 */
class Virus: public Unit
{
    public:
        /*! Creates a Virus with default position and speed
        */
        Virus() :
            Unit(UnitType::virus, 5),
            frame_count(0)
        {}

        /*! Creates a Virus
        @param pos start position
        @param speed start speed
        */
        Virus(Coord pos,Coord speed) :
            Unit(pos, speed, UnitType::virus, 5),
            frame_count(0)
        {}

        /*! Updates the gameobject. Particularly, it allows the object to do
            something on a keypress, when it touches the walls of the screen
            or when it touches another object.
        @param mySDL screen which the Unit lives in. Used to determine the boundries.
        @param keyboardState state of the keyboard, used to identify key presses.
        @param objects list of all objects in the game (including this one), used to interact with other objects.
        */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            // Simply update the speed
            pos+=speed;

            // Despawn the virus when it hits the boundry. Note that we apply the radius to make sure it despawns when out of sight
            if (pos.x < -this->radius || pos.x > mySDL.size().x + this->radius || pos.y < -this->radius || pos.y > mySDL.size().y + this->radius) {
                // It's over
                objects.despawn(this);
            }

            // Bounce off other virusses
            for (GameObject* obj : objects.get_objects()) {
                // Skip all non-virusses & itself
                if (this == obj || obj->type != GameObjectType::unit || ((Unit*) obj)->unit_type == UnitType::player) { continue; }
                
                // Make sure they are touching each other
                Unit* unit = (Unit*) obj;
                if (this->distance_to(*unit) <= this->radius + unit->radius) {
                    // Compute the normal (quick 'n' dirty) and set it as our own speed
                    Coord normal = unit->point_to(*this);
                    this->speed.x += normal.x;
                    this->speed.y += normal.y;
                }
            }

            // Once every particle_interval frames, spawn a plus particle
            if (frame_count == particle_interval) {
                // Generate a randomized, normalized speed
                Coord speed(rand_0_1(), rand_0_1());
                double len = sqrt(speed.x * speed.x + speed.y * speed.y);
                speed.x /= len;
                speed.y /= len;

                objects.spawn((GameObject*) new PlusParticle(this->pos, speed));
            }

            // Increment the frame_count but keep it bounded
            frame_count = (frame_count + 1) % (particle_interval + 1);
        }
        
        /*! Draws the Virus
        @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(0,255,0));
        }

    private:
        unsigned int frame_count;
};

#endif
