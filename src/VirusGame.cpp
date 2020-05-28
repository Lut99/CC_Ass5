
#include "Utils.h"
#include "MySDL.h"
#include "Coord.h"
#include "Player.h"
#include "Virus.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/*! @file
   The starting point of VirusGame, holds the main() function.
*/
extern "C" int main(int argc, char* argv[])
{
    srand(time(NULL));        // seed the speudo random number generator 
    MySDL mySDL("VirusGame"); // create an SDL graphics window
    
    Player player(mySDL.size()*0.5); // player

    const int max_nr_units=20;    // maximum number of units, feel free to change
    int nr_units=0;               // current number of units
    Virus units[max_nr_units];    // holds all units in the game
    double new_virus_chance=0.01; // the chance that a new virus is created each time step
    double new_virus_max_speed=3; // maximum speed of a new virus
    
    bool quit=false;
    while (!quit) // the game loop
    {
        int ticks_start=SDL_GetTicks();
        SDL_SetRenderDrawColor(mySDL.renderer(),0,0,0,255); // black background
        SDL_RenderClear(mySDL.renderer()); // clear graphics window

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
                std::cout<<"mouse down: "<<x<<","<<y<<'\n';
                break;
            }
        }
        const Uint8* keyboardState=SDL_GetKeyboardState(NULL); // get keyboard state

        player.keyboard(keyboardState); // control the player by keyboard
        player.step(mySDL);
        player.draw(mySDL);
        
        if (rand_0_1()<new_virus_chance && nr_units<max_nr_units) // by chance create new virus
        {
            Coord window_size=mySDL.size();
            Coord pos  = Coord(window_size.x       * rand_0_1() ,  window_size.y       * rand_0_1() );
            Coord speed= Coord(new_virus_max_speed * rand_m1_1(),  new_virus_max_speed * rand_m1_1());
            units[nr_units]=Virus(pos,speed);
            nr_units+=1;
        }
        for (int i=0;i<nr_units;i++) // handle all units
        {
            units[i].step(mySDL);
            units[i].draw(mySDL);
        }
        
        SDL_RenderPresent(mySDL.renderer()); // update graphics window
        int frame_ticks=SDL_GetTicks()-ticks_start;
        if( frame_ticks < SCREEN_TICKS_PER_FRAME ) SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks ); // delay for right framerate
    }
    return 0;
}
