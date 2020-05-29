
#include <algorithm>
#include <SDL2/SDL_ttf.h>

#include "GameState.h"
#include "Utils.h"
#include "MySDL.h"
#include "Coord.h"
#include "Unit.h"
#include "Player.h"
#include "Virus.h"
#include "EvilVirus.h"
#include "EndText.h"
#include "EndAnimation.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/*! @file
   The starting point of VirusGame, holds the main() function.
*/
extern "C" int main(int argc, char* argv[])
{
    srand(time(NULL));        // seed the speudo random number generator 
    MySDL mySDL("VirusGame"); // create an SDL graphics window

    double player_good_virus_charge=5; // the amount of charge the player gets when eating a good virus
    double player_evil_virus_charge=15; // the amount of charge the player loses when eating an evil virus

    double virus_max = 15; // the maximum number of good virusses in play
    double virus_chance=0.05; // the chance that a new virus is created each time step
    double virus_max_speed=3; // maximum speed of a new virus play

    double evil_virus_max = 15; // the maximum number of evil virusses in play
    double evil_virus_chance=0.005; // the chance that a new evil virus is created each time step
    double evil_virus_speed=0.5; // acceleration towards to player of the evil virus
    unsigned int evil_virus_lifetime=300; // number in frames before the evil virus gives up and stops chasing the player

    // Initialize the GameState object with the maximum number of good and evil virusses, respectively
    GameState state(virus_max, evil_virus_max);

    // Immediately add the player
    state.add((GameObject*) new Player(mySDL.size()*0.5, player_good_virus_charge, player_evil_virus_charge));

    // Initialize the TFF library
    if (TTF_Init() < 0) {
        throw std::runtime_error("Could not initialize font library.");
    }
    
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
        for (GameObject* obj : state.get_objects()) {
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
            Player* player = (Player*) state.get_player();
            if (player->get_charge() >= 100) {
                state.add((GameObject*) new EndText(mySDL, true));
                state.add((GameObject*) new EndAnimation(true));
                won = true;
            } else if (player->get_charge() <= -100) {
                state.add((GameObject*) new EndText(mySDL, false));
                state.add((GameObject*) new EndAnimation(false));
                lost = true;
            }
        }

        // Potentially spawn any new good virusses
        if (!won && !lost && rand_0_1() < virus_chance && state.get_good_count() < state.max_good_count)
        {
            Coord window_size=mySDL.size();

            // Choose a random position and speed, but make sure we do not spawn at the edge entirely
            Coord pos = Coord(10 + (window_size.x - 20) * rand_0_1(), 10 + (window_size.y - 20) * rand_0_1());
            Coord speed = Coord(virus_max_speed * rand_m1_1(),  virus_max_speed * rand_m1_1());

            // Add it immediately
            state.add((GameObject*) new Virus(pos,speed));
        }
        // Potentially spawn any new evil virusses
        if (!won && !lost && rand_0_1() < evil_virus_chance && state.get_evil_count() < state.max_evil_count)
        {
            Coord window_size=mySDL.size();

            // Choose a random position and speed, but make sure we do not spawn at the edge entirely
            Coord pos = Coord(10 + (window_size.x - 20) * rand_0_1(), 10 + (window_size.y - 20) * rand_0_1());

            // Add it immediately
            state.add((GameObject*) new EvilVirus(pos, evil_virus_speed, evil_virus_lifetime));
        }

        /*** WAIT PHASE ***/
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }

    // Stop TTF
    TTF_Quit();

    return 0;
}
