
#include <algorithm>

#include "GameState.h"
#include "Utils.h"
#include "MySDL.h"
#include "Coord.h"
#include "Unit.h"
#include "Player.h"
#include "Virus.h"
#include "EvilVirus.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/*! @file
   The starting point of VirusGame, holds the main() function.
*/
extern "C" int main(int argc, char* argv[])
{
    srand(time(NULL));        // seed the speudo random number generator 
    MySDL mySDL("VirusGame"); // create an SDL graphics window

    const int max_virus=20;    // maximum number of good virusses, feel free to change
    double new_virus_chance=0.05; // the chance that a new virus is created each time step
    double new_virus_max_speed=3; // maximum speed of a new virus play

    const int max_evil_virus=10;       // Maximum number of evil virusses
    double new_evil_virus_chance=0.005; // the chance that a new evil virus is created each time step
    double new_evil_virus_speed=0.15; // acceleration towards to player of the evil virus

    // Initialize the GameState object
    GameState state;

    // Immediately add the player
    state.add((GameObject*) new Player(mySDL.size()*0.5));
    
    bool won = false;
    bool lost = false;
    bool quit=false;
    while (!quit) // the game loop
    {
        /*** DRAW PHASE ***/

        // Clean the frame
        int ticks_start=SDL_GetTicks();
        SDL_SetRenderDrawColor(mySDL.renderer(),0,0,0,255); // black background
        SDL_RenderClear(mySDL.renderer()); // clear graphics window

        // Draw all objects
        for (auto& obj : state.get_objects()) {
            obj->draw(mySDL);
        }

        // Serve the frame to the user
        SDL_RenderPresent(mySDL.renderer());

        /*** SDL EVENTS PHASE ***/
        SDL_Event e;
        while( SDL_PollEvent(&e) ) // handle events
        {
            int x, y;
            switch(e.type)
            {
            case SDL_QUIT:
                quit = true; break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState( &x, &y );
                // std::cout<<"mouse down: "<<x<<","<<y<<'\n';
                break;
            }
        }
        const Uint8* keyboardState=SDL_GetKeyboardState(NULL); // get keyboard state

        /*** UPDATE PHASE ***/

        // Update all objects
        for (GameObject* obj : state.get_objects()) {
            // ...except do units & matching particles when the game has been decided
            if ((won || lost) && obj->type == GameObjectType::unit) {
                continue;
            } else if (obj->type == GameObjectType::particle) {
                Particle* prt = (Particle*) obj;
                if ((won || lost) && (prt->particle_type == ParticleType::plus || prt->particle_type == ParticleType::min)) {
                    continue;
                }
            }

            // Update the object
            obj->update(mySDL, keyboardState, state);
        }

        // Update the state to propagate all adds and removals
        state.update();

        // Check for the win / lose condition
        if (!won && !lost) {
            Player* player = (Player*) state.get_objects().at(0);
            if (player->get_charge() >= 1.0) {
                std::cout << "You won!!!" << std::endl;
                won = true;
            } else if (player->get_charge() <= -1.0) {
                std::cout << "You lost..." << std::endl;
                lost = true;
            }
        }

        // Potentially spawn any new good virusses
        if (!won && !lost && rand_0_1() < new_virus_chance && state.get_good_count() < max_virus)
        {
            Coord window_size=mySDL.size();

            // Choose a random position and speed, but make sure we do not spawn at the edge entirely
            Coord pos = Coord(10 + (window_size.x - 20) * rand_0_1(), 10 + (window_size.y - 20) * rand_0_1());
            Coord speed = Coord(new_virus_max_speed * rand_m1_1(),  new_virus_max_speed * rand_m1_1());

            // Add it immediately
            state.add((GameObject*) new Virus(pos,speed));
        }
        // Potentially spawn any new evil virusses
        if (!won && !lost && rand_0_1() < new_evil_virus_chance && state.get_evil_count() < max_evil_virus)
        {
            Coord window_size=mySDL.size();

            // Choose a random position and speed, but make sure we do not spawn at the edge entirely
            Coord pos = Coord(10 + (window_size.x - 20) * rand_0_1(), 10 + (window_size.y - 20) * rand_0_1());

            // Add it immediately
            state.add((GameObject*) new EvilVirus(pos, new_evil_virus_speed));
        }

        /*** WAIT PHASE ***/
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }

    return 0;
}
