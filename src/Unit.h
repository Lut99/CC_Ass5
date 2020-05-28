/* UNIT.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *
 * Created:
 *   5/28/2020, 4:41:23 PM
 * Last edited:
 *   5/29/2020, 1:27:58 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Unit class forms the baseclass of both the Virus and Human
 *   classes
**/

#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED

#include <map>
#include <ostream>
#include <cmath>

#include "GameObject.h"

/*! Enum which dictates the type of the Unit, so that it can be identified later.
 */
enum class UnitType {
    player,
    virus,
    evil_virus
};

/*! Static list which converts enums to their correct radiuses.
 */
static std::map<UnitType, const int> type_to_radius = {
    {UnitType::player, 25},
    {UnitType::virus, 10},
    {UnitType::evil_virus, 10}
};

/*! Baseclass for both Virusses and Players.
 */
class Unit: public GameObject {
    protected:
        Coord speed;

        /*! Creates the unit with the default Coord values. Only the radius needs to be specified.
          @param radius the radius of the unit
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        Unit(const UnitType type, int layer = 0)
          : GameObject(GameObjectType::unit, layer),
          unit_type(type),
          radius(type_to_radius[type])
        {}
      
        /*! Creates the unit with the given values.
          @param position the initial position of the agent
          @param speed the initial speed (which incorporates direction) of the unit
          @param radius the radius of the unit
         */
        Unit(Coord position, Coord speed, const UnitType type, int layer = 0)
            : GameObject(position, GameObjectType::unit, layer),
            speed(speed),
            unit_type(type),
            radius(type_to_radius[type])
        {}

    public:
        const UnitType unit_type;
        const int radius;

        /*! Computes the distance between this Unit and the given Unit
          @param u the other Unit to compute the distance to.
        */
        double distance_to(const Unit& u) const {
            double dx = this->pos.x - u.pos.x;
            double dy = this->pos.y - u.pos.y;
            return sqrt(dx * dx + dy * dy);
        }

        /*! Returns a normalized vector that points from this unit to another
          @param u the other Unit to point to.
        */
        Coord point_to(const Unit& u) const {
            // Do the other vector minus this vector
            double x = u.pos.x - this->pos.x;
            double y = u.pos.y - this->pos.y;

            // Normalize
            double len = sqrt(x * x + y * y);
            x /= len;
            y /= len;

            // Return as coord
            return Coord(x, y);
        }

        /*! Gives operator<< access to this unit
         */
        friend std::ostream& operator<<(std::ostream& os, const Unit& u);
};

/*! Prints the position of a Unit as UID
  @param os output stream to write to
  @param u the unit to write to the stream
  */
std::ostream& operator<<(std::ostream& os, const Unit& u) {
  os << "(" << u.pos.x << "," << u.pos.y << ")";
  return os;
}

#endif
