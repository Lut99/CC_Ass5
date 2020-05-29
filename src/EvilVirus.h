/* EVIL VIRUS.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/29/2020, 12:00:30 AM
 * Last edited:
 *   5/29/2020, 11:07:37 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The evil counterpart of the Virus. Will damage the player when hit,
 *   and even actively search for it. Also features little red minusses
 *   and an erratic shake.
**/

#ifndef EVILVIRUS_INCLUDED
#define EVILVIRUS_INCLUDED

#include <iostream>
#include <map>

#include "MySDL.h"
#include "Utils.h"
#include "Coord.h"
#include "Unit.h"
#include "Player.h"
#include "MinParticle.h"

extern const unsigned int particle_interval;

/*! An EvilVirus - bad stuff comes your way!
 */
class EvilVirus: public Unit
{
    private:
        unsigned int frame_count;
        double dmg;
        double acc;
        unsigned int lifetime;

    public:
        /*! Creates a EvilVirus with default position
          @param acceleration the amount the evil virus will accelerate to the player each turn
          @param lifetime number of frames that the virus behaves intelligently before it stops actively following the player
         */
        EvilVirus(double acceleration = 0.5, unsigned int lifetime = 600) :
            Unit(UnitType::evil_virus, 5),
            frame_count(0),
            acc(acceleration * (rand_0_1() * 0.2 + 0.9)),
            lifetime(lifetime)
        {}

        /*! Creates an EvilVirus
          @param pos start position
          @param acceleration the amount the evil virus will accelerate to the player each turn
          @param lifetime number of frames that the virus behaves intelligently before it stops actively following the player
         */
        EvilVirus(Coord pos, double acceleration = 0.5, unsigned int lifetime = 600) :
            Unit(pos, Coord(0, 0), UnitType::evil_virus, 5),
            frame_count(0),
            acc(acceleration * (rand_0_1() * 0.2 + 0.9)),
            lifetime(lifetime)
        {}

        /*! Creates an EvilVirus, but with a certain starting speed and direction other than 0, 0.
          @param pos start position
          @param speed the initial speed and direction of the virus
          @param acceleration the amount the evil virus will accelerate to the player each turn
          @param lifetime number of frames that the virus behaves intelligently before it stops actively following the player
         */
        EvilVirus(Coord pos, Coord speed, double acceleration = 0.5, unsigned int lifetime = 600) :
            Unit(pos, speed, UnitType::evil_virus, 5),
            frame_count(0),
            acc(acceleration * (rand_0_1() * 0.2 + 0.9)),
            lifetime(lifetime)
        {}

        /*! Updates the evil virus. Note that this virus will actively seek out
            the player: it will add 0.5 speed to itself each frame pointing
            towards the player. Stops once it dies by hitting the player or the
            wall.
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8*, GameState& objects) {
            Player* player = (Player*) objects.get_player();

            // Only target & slow down if we are alive
            if (this->frame_count < this->lifetime) {
                // Get the directional vector pointing towards the player
                Coord vec = this->point_to(*((Unit*) player));
                
                // Add that vector to the internal vector
                this->speed.x += vec.x * this->acc;
                this->speed.y += vec.y * this->acc;

                // However, to aid the virus, we give it the same drag as the player
                this->speed.x *= 0.95;
                this->speed.y *= 0.95;
            }

            // Apply the speed
            pos+=speed;

            // If we hit another friendly virus, despawn us both
            #define LOG(MIDDLE) std::cout << MIDDLE << std::endl
            for (GameObject* obj : objects.get_objects()) {
                // Skip all non-units & players
                if (obj->type != GameObjectType::unit || ((Unit*) obj)->unit_type == UnitType::player) { continue; }

                // Compute the distance to the virus - but make sure we aren't computing a distance to ourselves
                Unit* unit = (Unit*) obj;
                if (this != unit && this->distance_to(*unit) <= this->radius + unit->radius) {
                    // Make the virusses bounce off of each other

                    // Compute the normal (quick 'n' dirty) and set it as our own speed
                    Coord normal = unit->point_to(*this);
                    this->speed.x += normal.x;
                    this->speed.y += normal.y;

                    // Only if it's a good virus and we are not yet on our max, convert to an evil virus
                    if (unit->unit_type == UnitType::virus && objects.get_evil_count() < objects.max_evil_count) {
                        objects.spawn((GameObject*) new EvilVirus(unit->pos, unit->speed, this->acc, this->lifetime));

                        // Remove the other unit
                        objects.despawn((GameObject*) unit);
                    }
                }
            }

            // Despawn the virus when it hits the boundry. Note that we apply the radius to make sure it despawns when out of sight
            if (pos.x < -this->radius || pos.x > mySDL.size().x + this->radius || pos.y < -this->radius || pos.y > mySDL.size().y + this->radius) {
                // It's over
                objects.despawn(this);
            }

            // Once every particle_interval frames, spawn a min particle
            if (frame_count % particle_interval == 0) {
                // Generate a randomized, normalized speed
                Coord speed(rand_0_1(), rand_0_1());
                double len = sqrt(speed.x * speed.x + speed.y * speed.y);
                speed.x /= len;
                speed.y /= len;

                objects.spawn((GameObject*) new MinParticle(this->pos, speed));
            }

            // Increment the frame_count but keep it bounded
            frame_count++;
        }
        
        /*! Draws the Virus
        @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            // Add up to 2 randomly to pos.x and / or pos.y to create erratic shaking
            Coord animated_pos = this->pos;

            animated_pos.x += rand_0_1() * 5;
            animated_pos.y += rand_0_1() * 5;
            
            // Decrease red if the virus isn't alive anymore
            int red = 255;
            if (this->frame_count >= this->lifetime) {
                red /= 2;
            }

            filledCircleColor(mySDL.renderer(), animated_pos.x, animated_pos.y, this->radius, color(red,0,0));
        }
};

#endif

