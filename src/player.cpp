// debugging
#include <iostream>

// input array
#include <array>

// drawing and collision rect
#include <SDL2/SDL.h>

// storing 2D vector quantities
#include "vec2.cpp"

using namespace std;


Vec2 scaleVec2(Vec2 vector, double scalar)
{
    Vec2 returnVector;

    returnVector.x = vector.x * scalar;
    returnVector.y = vector.y * scalar;

    return returnVector;
}

class Player
{
    public:
        Player()
        {
            gravityVector.y = 5;

            inputAcceleration = 50;

            hitbox.w = 32;
            hitbox.h = 32;
            updateHitboxPosition();
        }

        void handleEvents(array<bool, 7> inputArray)
        {
            if (inputArray[0]) acceleration.y -= inputAcceleration; // up arrow
            if (inputArray[1]) acceleration.x += inputAcceleration; // right arrow
            if (inputArray[2]) acceleration.y += inputAcceleration; // down arrow
            if (inputArray[3]) acceleration.x -= inputAcceleration; // left arrow
        }

        void tick(double delta)
        {
            acceleration.scale(delta);

            acceleration.add(gravityVector);

            acceleration.add(scaleVec2(velocity, -0.01));

            velocity.add(acceleration);

            acceleration.zero();

            position.add(scaleVec2(velocity, delta));

            updateHitboxPosition();
        }

        void draw(SDL_Renderer *renderer)
        {
            cout << "drawing player" << endl;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &hitbox);
        }
    private:
        Vec2 position;
        Vec2 previousPosition;
        Vec2 velocity;
        Vec2 acceleration;
        Vec2 gravityVector;

        double inputAcceleration; 

        SDL_Rect hitbox;

        void updateHitboxPosition()
        {
            hitbox.x = static_cast <int> (floor(position.x));
            hitbox.y = static_cast <int> (floor(position.y));
        }
};
