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
            gravityVector.y = 100;

            inputAcceleration = 2500;

            airResistance = 0.05;

            hitbox.w = 32;
            hitbox.h = 32;
            updateHitboxPosition();
        }

        void updateInputs(array<bool, 7> newInputArray)
        {
            for (int i = 0; i < 7; i++)
            {
                inputArray[i] = newInputArray[i];
            }
        }

        void tick(double delta)
        {
            if (inputArray[0]) acceleration.y -= inputAcceleration; // up arrow
            if (inputArray[1]) acceleration.x += inputAcceleration; // right arrow
            if (inputArray[2]) acceleration.y += inputAcceleration; // down arrow
            if (inputArray[3]) acceleration.x -= inputAcceleration; // left arrow

            acceleration.add(gravityVector);

            acceleration.add(scaleVec2(velocity, -1 * airResistance));

            acceleration.scale(delta);

            velocity.add(acceleration);

            acceleration.zero();

            position.add(scaleVec2(velocity, delta));

            updateHitboxPosition();
        }

        void draw(SDL_Renderer *renderer)
        {
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

        double airResistance;

        SDL_Rect hitbox;

        array<bool, 7> inputArray;

        void updateHitboxPosition()
        {
            hitbox.x = static_cast <int> (floor(position.x));
            hitbox.y = static_cast <int> (floor(position.y));
        }
};
