# Design choises
Game loop: The delta time value is saved to a singleton and can only be changed by the minigin run function. This to prevent other classes from acidentily changing the value of delta time. Apart from that delta time can be read from anywhere in the program. Fixed update has a fixed time stap wich is given as parameter to the function. The function is only used for physics calculations and networking, the parameter is added to enshure the right time value is used in the calculations.

Game object: The game object is a container class for all game components. It requires a transform struct to be created, the reason for this is that every object needs to have a place in the level even if this value is never used. Game components are all derived from the base class BaseComponent wich requires a pointer to a GameObject to be created. This to make shure that a game component can not exist on its own.**NOTE** The game object pointer in BaseComponent will be changed to a weak pointer in the future to prevent game components from acidentaly deleting the game object they are bound to. Every game component has the folowing functions: Update, FixedUpdate and Render. If any of these functions do not apply to the component they are defined as ampty functions. **NOTE** Check if executing empty functions slows down the game or not, if it does find a solution. Curently the render function of the components require x and y parameters, this will later be replaced with a call to the game objects transform struct.

# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. 

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project with some of the scaffolding in place to get started. None of the patterns discussed in the course are used yet (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.
