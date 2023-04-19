#include <iostream> // debugging

#include <array> // used for vector quantities (array<double, 2>)

#include <SDL2/SDL.h> // used for drawing and collision rect

#include "vec2.cpp" // used for storing 2D vector quantities

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
            gravityVector.y = 0.5;

            hitbox.w = 32;
            hitbox.h = 32;
            updateHitboxPosition();
        }

        void handleEvents(array<bool, 7> inputArray)
        {
            if (inputArray[0]) // up arrow
            {
                acceleration.y -= 0.1;
            }
            if (inputArray[1]) // right arrow
            {
                acceleration.x += 0.1;
            }
            if (inputArray[2]) // down arrow
            {
                acceleration.y += 0.1;
            }
            if (inputArray[3]) // left arrow
            {
                acceleration.x -= 0.1;
            }
        }

        void tick()
        {
            acceleration.add(gravityVector);

            acceleration.add(scaleVec2(velocity, -0.01));

            velocity.add(acceleration);

            acceleration.zero();

            position.add(velocity);

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

        SDL_Rect hitbox;

        void updateHitboxPosition()
        {
            hitbox.x = static_cast <int> (floor(position.x));
            hitbox.y = static_cast <int> (floor(position.y));
        }
};
