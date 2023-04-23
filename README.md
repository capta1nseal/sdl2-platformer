# sdl2-2d-game

A fun little free-time project to develop my c++ and game design skills

## Authors and acknowledgment

Created by Aidan Walker
Thanks to SDL2's devs, it handles the hardware and lets the developer focus on everything else (plus it has some good simple features for games)

## License

Licensed under the GNU general public license version 3 (GPL 3.0). The license can be found in the root folder of the project.

For the uninitiated, that means this program and its source code are very free to distribute and modify. I encourage you to do some research on licenses if you want to know more. A great place to start is creative commons.

## Project status

The project is very WIP - for example, no art is being drawn yet, there is no level editor, and collision isn't implemented fully

### Features

- player with realistic movement physics simulation
- camera that follows the player and has an adjustable level of zoom
- collider objects (WIP)
- very tight execution (within microseconds of perfect deltas on stable systems)

- Planned:
- art
- easy-to-use level editor with features like parallax art layers and pixel-perfect asset placement
- multiple levels

#### What I've learned
- Before starting this project, I kinda knew what pointers are and had passed them around to third party libraries, for example, but had never implemented any code of my own that made use of them. This is mostly due to being lazy and sticking with python for too long. Now no objects of notable size are passed in functions, and pointers are used instead.
- How to use decomposition in practice to split the project into reasonably-sized pieces
- Making the physics simulation function with realistic properties and variable time deltas has been a nice challenge
- Getting the execution to run with accurate timings wasn't as simple as expected
