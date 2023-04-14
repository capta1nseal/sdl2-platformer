#include <iostream>
#include <array>
#include <SDL2/SDL.h>

using namespace std;

class Player
{
    public:
        Player(SDL_Colour setColour)
        {
            cout << "initialising player object" << endl;

            position = {0.0, 0.0};
            previousPosition = {0.0, 0.0};
            velocity = {0.0, 0.0};
            acceleration = {0.0, 0.0};

            hitbox.w = 16;
            hitbox.h = 16;
            hitbox.x = static_cast <int> (floor(position[0]));
            hitbox.y = static_cast <int> (floor(position[1]));

            colour = setColour;
        }
    private:
        array<double, 2> position;
        array<double, 2> previousPosition;
        array<double, 2> velocity;
        array<double, 2> acceleration;

        SDL_Rect hitbox;

        SDL_Colour colour;
        
        void tick()
        {
            velocity[0] += acceleration[0];
            velocity[1] += acceleration[1];

            position[0] += velocity[0];
            position[1] += velocity[1];

            acceleration[0] = 0;
            acceleration[1] = 0;
        }

        void draw(SDL_Renderer *renderer)
        {
            cout << "drawing player" << endl;

            
        }
};
