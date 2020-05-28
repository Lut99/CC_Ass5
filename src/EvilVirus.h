/* EVIL VIRUS.h
 *   by Anonymous
 *
 * Created:
 *   5/29/2020, 12:00:30 AM
 * Last edited:
 *   5/29/2020, 1:29:49 AM
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

    public:
        /*! Creates a EvilVirus with default position
          @param damage the amount of charge that is deducted from the player when it is hit by an EvilVirus
          @param acceleration the amount the evil virus will accelerate to the player each turn
         */
        EvilVirus(double damage = 2, double acceleration = 0.5) :
            Unit(UnitType::evil_virus, 5),
            frame_count(0),
            dmg(damage),
            acc(acceleration)
        {}

        /*! Creates an EvilVirus
          @param pos start position
          @param damage the amount of charge that is deducted from the player when it is hit by an EvilVirus
          @param acceleration the amount the evil virus will accelerate to the player each turn
         */
        EvilVirus(Coord pos, double damage = 2, double acceleration = 0.5) :
            Unit(pos, Coord(0, 0), UnitType::virus, 5),
            frame_count(0),
            dmg(damage),
            acc(acceleration)
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

            // Get the directional vector pointing towards the player
            Coord vec = this->point_to(*((Unit*) player));
            
            // Add that vector to the internal vector
            this->speed.x += vec.x * this->acc;
            this->speed.y += vec.y * this->acc;

            // However, to aid the virus, we give it the same drag as the player
            this->speed.x *= 0.95;
            this->speed.y *= 0.95;

            // Apply the speed
            pos+=speed;

            // Apply penalty to the player and despawn when we hit the edge
            if (this->distance_to(*((Unit*) player)) <= player->radius + this->radius) {
                // Deal damage
                player->hit(this->dmg);

                // Despawn ourselves
                objects.despawn(this);
            }

            // If we hit another friendly virus, despawn us both
            for (GameObject* obj : objects.get_objects()) {
                // Skip all non-units & players
                if (obj->type != GameObjectType::unit || ((Unit*) obj)->unit_type == UnitType::player) { continue; }

                // Compute the distance to the virus - but make sure we aren't computing a distance to ourselves
                Unit* unit = (Unit*) obj;
                if (this != unit && this->distance_to(*unit) <= this->radius + unit->radius) {
                    // Despawn 'em
                    objects.despawn(this);
                    objects.despawn(unit);
                }
            }

            // Despawn the virus when it hits the boundry. Note that we apply the radius to make sure it despawns when out of sight
            if (pos.x < -this->radius || pos.x > mySDL.size().x + this->radius || pos.y < -this->radius || pos.y > mySDL.size().y + this->radius) {
                // It's over
                objects.despawn(this);
            }

            // Once every particle_interval frames, spawn a min particle
            if (frame_count == particle_interval) {
                // Generate a randomized, normalized speed
                Coord speed(rand_0_1(), rand_0_1());
                double len = sqrt(speed.x * speed.x + speed.y * speed.y);
                speed.x /= len;
                speed.y /= len;

                objects.spawn((GameObject*) new MinParticle(this->pos, speed));
            }

            // Increment the frame_count but keep it bounded
            frame_count = (frame_count + 1) % (particle_interval + 1);
        }
        
        /*! Draws the Virus
        @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const {
            filledCircleColor(mySDL.renderer(), pos.x, pos.y, radius, color(255,0,0));
        }
};

#endif

