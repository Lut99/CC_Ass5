/* GAME STATE.h
 *   by Tim Müller (11774606)
 * 
 * C++ ASSIGNMENT 5 (VIRUS GAME)
 *   > build on KDE Neon (Ubuntu 18.04) using GCC 7.5.0
 *   > Note: requires libsdl2-ttf-dev to be installed
 *
 * Created:
 *   5/28/2020, 11:03:28 PM
 * Last edited:
 *   5/29/2020, 11:07:36 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   This class stores the current game state. In particular, it stores a
 *   list of all objects, and then some vectors to allow delayed adding and
 *   removing objects. Finally, it also keeps track of the number of good
 *   and evil virusses.
**/

#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// Declare the GameState forwardly to enable cross-referencing
class GameState;

#include "GameObject.h"
#include "Unit.h"

class GameState {
    private:
        /*! List of objects in the game
         */
        std::vector<GameObject*> objects;
        /*! Is equal to the number of good virusses in the game
         */
        unsigned int good_virus_count;
        /*! Is equal to the number of evil virusses in the game
         */
        unsigned int evil_virus_count;

        /*! Temporary list of objects that is used to add in a delayed fashion
         */
        std::vector<GameObject*> to_add;
        /*! Temporary list of objects that is used to mark for removal
         */
        std::vector<GameObject*> to_remove;
        /*! Represents the change in good virusses before update() is called
         */
    
    public:
        /*! Stores the maximum number of good virusses allowed in the game
         */
        const unsigned int max_good_count;
        /*! Stores the maximum number of evil virusses allowed in the game
         */
        const unsigned int max_evil_count;


        /*! Creates a new GameState object. All lists will be empty, and all
            values will be 0.
         */
        GameState(const unsigned int max_good_count, const unsigned int max_evil_count) :
            good_virus_count(0),
            evil_virus_count(0),
            max_good_count(max_good_count),
            max_evil_count(max_evil_count)
        {}

        /*! Destructor for the GameState obejct. Will delete all pointers in
            the three lists.
         */
        ~GameState() {
            for (GameObject* obj : this->objects) {
                delete obj;
            }

            for (GameObject* obj : this->to_add) {
                delete obj;
            }

            for (GameObject* obj : this->to_remove) {
                delete obj;
            }
        }

        /*! Immediately adds a new GameObject to the state.
          @param obj the object to add
         */
        void add(GameObject* obj) {
            this->objects.push_back(obj);

            // Also update good or bad counters
            if (obj->type == GameObjectType::unit) {
                Unit* unit = (Unit*) obj;
                if (unit->unit_type == UnitType::virus) {
                    this->good_virus_count++;
                } else if (unit->unit_type == UnitType::evil_virus) {
                    this->evil_virus_count++;
                }
            }
        }

        /*! Schedules a new GameObject to be added. Will actually be done so
            when GameState::update() is called.
          @param obj the object to add
         */
        void spawn(GameObject* obj) {
            this->to_add.push_back(obj);

            // Also update good or bad counters
            if (obj->type == GameObjectType::unit) {
                Unit* unit = (Unit*) obj;
                if (unit->unit_type == UnitType::virus) {
                    this->good_virus_count++;
                } else if (unit->unit_type == UnitType::evil_virus) {
                    this->evil_virus_count++;
                }
            }
        }

        /*! Schedules an existing GameObject to be removed. Will actually be
            done so when GameState::update() is called.
          @param obj the object to add
         */
        void despawn(GameObject* obj) {
            this->to_remove.push_back(obj);

            // Already apply the counters
            if (obj->type == GameObjectType::unit) {
                Unit* unit = (Unit*) obj;
                if (unit->unit_type == UnitType::virus) {
                    this->good_virus_count--;
                } else if (unit->unit_type == UnitType::evil_virus) {
                    this->evil_virus_count--;
                }
            }
        }

        /*! Actually applies any scheduled removes and adds (in that order).
         */
        void update() {
            // First, remove all that need to be removed
            this->objects.erase(
                std::remove_if(
                    this->objects.begin(), this->objects.end(),
                    [this](GameObject* obj) {
                        if (std::find(this->to_remove.begin(), this->to_remove.end(), obj) != this->to_remove.end()) {
                            // Delete the pointer
                            delete obj;
                            return true;
                        }
                        return false;
                    }
                ),
                this->objects.end()
            );

            // Next, add all elements that need to be added
            this->objects.insert(this->objects.end(), this->to_add.begin(), this->to_add.end());

            // Finally, reset all temporary values
            this->to_add.clear();
            this->to_remove.clear();

            // As a bonus, sort the list based on layer
            std::sort(this->objects.begin(), this->objects.end(), [](GameObject* obj1, GameObject* obj2){
                return obj1->get_layer() > obj2->get_layer();
            });
        }

        /*! Returns a reference to the player.
         */
        GameObject* get_player() const {
            return (GameObject*) *(std::find_if(this->objects.begin(), this->objects.end(), [](GameObject* obj){
                return obj->type == GameObjectType::unit && ((Unit*) obj)->unit_type == UnitType::player;
            }));
        }

        /*! Returns a reference to the internal objects list.
         */
        const std::vector<GameObject*>& get_objects() const {
            return this->objects;
        }

        /*! Returns the count of good virusses
         */
        unsigned int get_good_count() const {
            return this->good_virus_count;
        }

        /*! Returns the count of evil virusses
         */
        unsigned int get_evil_count() const {
            return this->evil_virus_count;
        }
};

#endif

