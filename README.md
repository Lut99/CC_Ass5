# VirusGame #
A simple game build using the SDL2 graphics library. Use
the cursor keys to move to escape/kill the viruses.

![Alt text](VirusGame.png)

## Install

### Linux/Mac:

Using the package manager on your system to install:

    cmake
    git
    libsdl2-dev
    libsdl2-gfx-dev

For example for Ubuntu use:

    sudo apt install cmake git libsdl2-dev libsdl2-gfx-dev

For example for a Mac probably something like (run 'brew search sdl' to see which are available):

    brew install cmake git sdl sdl_gfx

Then:

    git clone https://bterwijn@bitbucket.org/bterwijn/virusgame.git
    cd virusgame/src
    mkdir build
    cd build
    cmake ..
    make
    ./VirusGame

### Windows:

Install [git](https://git-scm.com/download/win) and clone
[VirusGame](https://bitbucket.org/bterwijn/virusgame/src/master).

Install [Visual Studio Studio Community
2019](https://visualstudio.microsoft.com/) and in the Visual Studio
Installer install Worksload "Desktop development with C++" (includes
CMake).

Install the SDL2 graphics library use
[vcpkg](https://github.com/Microsoft/vcpkg) by using:

    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    .\vcpkg.exe integrate install
    .\vcpkg.exe install sdl2
    .\vcpkg.exe install sdl2-gfx --triplet x64-windows

Then in Visual Studio Studio Community 2019 open the virusgame/src
folder and build the project (F7) and run it (F5).


## Documentation
For documentation see the 
[list of classes]( http://sbt.science.uva.nl/bterwijn/virusgame/doc/html/annotated.html "Doxygen documentation")


## Author
Bas Terwijn <<b.terwijn@uva.nl>>


## Description of extension by student

### Author
Tim Müller (11774606) <<mullertim99@gmail.com>>

### OS information
Compiled & runs on KDE Neon (Ubuntu 18.04) with GCC 7.4.0.  
Note: requires the extra SDL2-library SDl2-TTF (```libsdl2-ttf-dev```) to be installed because of the text additions.

### How to run
Simply run CMake from a build directory to build it, followed by Make, and then to run the resulting 'VirusGame' executable.

### Changes overview
Now follows an overview of the added / changed features to the game. There may possible be other, smaller changes, but this should cover the most of it.

Files that I have added are:
  - EndAnimation.h
  - EndText.h
  - EvilVirus.h
  - FireworkParticle.h
  - FlavourText.h
  - GameObject.h
  - GameState.h
  - MinParticle.h
  - Particle.h
  - PlusParticle.h
  - RainParticle.h
  - Text.h
  - Unit.h

Files that I have changed are:
  - CMakeLists.txt
  - Player.h
  - Virus.h
  - VirusGame.cpp

And now for the promised list of features:

#### Gameplay features
  - The player can now eat good (green) virusses to obtain Charge
  - Evil virusses (red) have been introduced
  - Evil virusses chase the player
  - When an evil virus touches the player, he or she loses Charge
  - Evil virusses can convert good virusses to evil virusses upon touch
  - After a while, Evil virusses 'die' and stop behaving intelligently; they just keep floating with the same velocity and heading.  
  Note: they are still dangerous upon touch, and can also still infect good virusses
  - All virusses can leave the screen now, and then despawn
  - When the player collects enough charge, he or she wins
  - When the player loses enough charge, he or she loses

#### Animations
  - A win screen has been added
  - A defeat screen has been added
  - Good virusses emit a trail of green plusses
  - Evil virusses emit a trail of red minusses
  - Evil virusses have an erratic shake animation
  - All Units bounce off each other instead of being able to overlay
  - Added a float text whenever the player gains or loses Charge to indicate how much he / she has to go until win / defeat

#### Code changes
  - 'Step' and 'Keyboard' have been merged into a single 'Update' function
  - A clear split of drawing and updating has been made, where updating is done after presenting the drawn frame
  - Created a structure of GameObjects:
      - GameObject (root node)
          - Units: the player, good virusses, bad virusses
          - Text: all the different Text objects used
          - Particles: all the different particles used
          - EndAnimation: a special, non-drawing object that generating the particles for the end screens
  - Storage of units (now objects) has been moved to a vector within GameState, which can delay adding and removal of objects to not mess with the loops
  - A layer system has been implemented to determine the draw order (Z-axis)
  - Added parameters for most of the game's settings, to tweak the difficulty

#### Bug fixes
  - Player is now unable to leave the screen when holding down the key against it

### Known issues:
We have not been able to fix all issues. Issues that are known to use are:
  - Very rarely, good virusses stop spawning for some reason. Hasn't occurred consistenly enough to be able to debug.  
  WORKAROUND: A restart of the game should do the trick.
