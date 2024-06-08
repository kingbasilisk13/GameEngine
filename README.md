# Notes
**sprites**: Sprites are re used from Sander De Keukelaere.
**Bugs**: The game crashes when closing the program during a level. Please first skip back to the main menu before closing the game.

# Design choises
**Player input**: There are separate functions for adding player input: a function for keyboard input and a function for controller input. The latter allows you to specify the index of the controller.

**Game component commands**: Game component commands are commands that are linked to a component and a level. When the level is deleted, the command also gets deleted.

**Render order**: Instead of directly rendering to the SDL renderer when render is called in the render component, it is saved in an ordered multimap. The key is an int value. Eventually, all items in the map get rendered starting from the lowest key value to the highest. This allows the user to specify a render order.

**Scene manager**: The scene manager keeps track of all scene objects in an unordered map. The key value is the name of the scene. This allows the user to select a scene by name.

**Event manager**: This is a very basic global event manager that broadcasts a string to all its observers. The purpose is that the string starts with a specific event name. After that, the string needs to be split on a specific character so the necessary variables can be extracted.

**Resource manager**: When a resource is requested, the manager first checks if it has been loaded before. If not, it loads the resource and stores a unique pointer to it in an unordered map. The key is the path to the resource.

**Animation component**: Assuming the animations are all part of one PNG, this component can be used in combination with the render component to create an animation by going over the PNG row by row, starting at the top left and ending at the bottom right.


**Git repo**

https://github.com/kingbasilisk13/GameEngine
