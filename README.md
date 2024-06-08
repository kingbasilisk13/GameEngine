# Notes
**sprites**: Her bruikt van Sander De Keukelaere.

# Design choises
**Game loop**: The delta time value is saved to a singleton and can only be changed by the minigin run function. This to prevent other classes from acidentily changing the value of delta time. Apart from that delta time can be read from anywhere in the program. Fixed update has a fixed time stap wich is given as parameter to the function. The function is only used for physics calculations and networking, the parameter is added to enshure the right time value is used in the calculations.

**Scene**: The scene is an object that keeps a list of shared pointers (Still debating if it is better to switch to unique pointers) to all the GameObjects in the scene. It calls the update, fixed update and render function on them. **NOTE** the handeling of the deletion of game objects still needs to be added to the update function.

**Game object**: The game object is a container class for all game components. It requires a transform struct to be created, the reason for this is that every object needs to have a place in the level even if this value is never used. Each GameObject has an update, fixed update and render function. **NOTE** Handeling the removal of components still needs to be added to the GameObjects update function. The game object uses a list of unique pointers to keep track of all its components.

**GameComponents**: Game components are all derived from the base class BaseComponent wich requires a pointer to a GameObject to be created. This to make shure that a game component can not exist on its own. Every game component has the folowing functions: Update, FixedUpdate and Render. If any of these functions do not apply to the component they are defined as empty functions. **NOTE** Check if executing empty functions slows down the game or not, if it does find a solution. Each component is responsible for 1 task and 1 task only. example: the fps component calculates the current fps each second, it then sends this info to the text component. **NOTE** still debating what the best way of comunication is. Curently the component checks if the game object has the required component for it to work(fps needs text component). This is done by storing a raw pointer to that component. Each update it checks if this point is a nullpoiter, if so it tries to get the component again. This could cause a lot of unesisery calls. Possible solution is giving the component the ability to automaticaly add the required component if it is missing. Other solution is adding a watcher that notifies all components when a new component is added. Last solution is making the component throw an error, not recomended because this will force the user to add component in a specifick order. 

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
