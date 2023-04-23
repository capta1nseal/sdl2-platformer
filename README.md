# sdl2-2d-game

A simple 2D game engine created from a minimal codebase in c++

## Authors and acknowledgment

Created by Aidan Walker

Thanks to SDL2's devs, it handles the hardware and lets the developer focus on everything else (plus it has some good simple features for games)

## Building

- To build this project, you will need SDL2 development libraries, and (possibly,  not yet implemented) nlohmann/json somewhere on your include path.
- If you're on linux and have the requisite libraries, just run "make build" from the root of the project to build
- Building on windows is not yet implemented but should be very simple, as no platform-dependent libraries or programs are used

## License

Licensed under the GNU general public license version 3 (GPL 3.0). The license can be found in the root folder of the project.

For the uninitiated, that means this program and its source code are very free to distribute and modify. I encourage you to do some research on licenses if you want to know more. A great place to start is creative commons.

## Project status

The project is very WIP - for example, no art is being drawn yet, there is no level editor, and collision isn't implemented fully

### Features

Current:
- player with realistic movement physics simulation
- camera that follows the player and has an adjustable level of zoom
- collider objects (WIP)
- very tight execution (within microseconds of perfect deltas on stable systems)

Planned:
- art
- easy-to-use level editor with features like parallax art layers and pixel-perfect asset placement
- multiple levels
