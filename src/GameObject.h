/* GAME OBJECT.h
 *   by Anonymous
 *
 * Created:
 *   5/28/2020, 9:34:54 PM
 * Last edited:
 *   5/29/2020, 1:26:57 AM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   GameObject forms the baseclass of everything that is shown on the
 *   screen.
**/

#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED

#include <vector>
#include <memory>

#include "GameState.h"
#include "MySDL.h"
#include "Coord.h"

/*! The type that a GameObject can take on
 */
enum class GameObjectType {
    text,
    unit,
    particle
};

/*! The most basic level of the object tree
 */
class GameObject {
    protected:
        Coord pos;
        int layer;
    
        /*! Creates a GameObject with default position.
          @param type type of the GameObject
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        GameObject(GameObjectType type, int layer = 0) :
            type(type)
        {}

        /*! Creates a GameObject with given position.
          @param position the initial position of the GameObject
          @param type type of the GameObject
          @param layer the layer in which to order the GameObjects. Higher means it will be drawn on top of lower layers.
         */
        GameObject(Coord position, GameObjectType type, int layer = 0) :
            pos(position),
            type(type)
        {}
    
    public:
        const GameObjectType type;

        /*! Updates the gameobject. Particularly, it allows the object to do
            something on a keypress, when it touches the walls of the screen
            or when it touches another object.
          @param mySDL screen which the Unit lives in. Used to determine the boundries.
          @param keyboardState state of the keyboard, used to identify key presses.
          @param objects list of all objects in the game (including this one), used to interact with other objects.
         */
        virtual void update(MySDL& mySDL, const Uint8* keyboardState, GameState& objects) = 0;

        /*! Allows the object to draw itself
          @param mySDL for the size of the window
        */
        virtual void draw(MySDL& mySDL) const = 0;

        /* Get the layer from the GameObject.
         */
        int get_layer() const {
            return this->layer;
        }
};

#endif
