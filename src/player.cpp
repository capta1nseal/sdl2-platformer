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
            gravityVector.y = 4000;

            walkAcceleration = 4000;
            jumpVelocity = 1000;

            jumpBonus = 30.0;
            airControl = 0.1;

            airResistance = 0.0002;
            surfaceFriction = 0.01;


            hitbox.w = 32;
            hitbox.h = 32;
            updateHitboxPosition();

            landing = false;
            onGround = true;
            jumping = false;
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
            jumping = false;
            if (inputArray[4] and onGround) // Z - jump
            {
                velocity.y -= jumpVelocity;
                jumping = true;
            }
            if (inputArray[1]) // right arrow
            {
                if (jumping) acceleration.x += walkAcceleration * jumpBonus;
                else if (onGround) acceleration.x += walkAcceleration;
                else acceleration.x += walkAcceleration * airControl;
            }
            if (inputArray[3]) // left arrow
            {
                if (jumping) acceleration.x -= walkAcceleration * jumpBonus;
                else if (onGround) acceleration.x -= walkAcceleration;
                else acceleration.x -= walkAcceleration * airControl;
            }

            acceleration.add(gravityVector);

            acceleration.scale(delta);

            acceleration.add(scaleVec2(velocity, -1 * airResistance));

            if (onGround)
            {
                acceleration.x -= velocity.x * surfaceFriction;
            }

            velocity.add(acceleration);

            acceleration.zero();

            previousPosition.setEqual(position);

            position.add(scaleVec2(velocity, delta));

            onGround = false;

            if (position.y > 1200 - hitbox.w)
            {
                velocity.y = 0.0;
                position.y = 1200.0 - hitbox.w;
                onGround = true;
            }

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

        bool landing;
        bool onGround;
        bool jumping;

        double walkAcceleration; 
        double jumpVelocity;

        double jumpBonus;
        double airControl;

        double airResistance;
        double surfaceFriction;

        SDL_Rect hitbox;

        array<bool, 7> inputArray;

        void updateHitboxPosition()
        {
            hitbox.x = static_cast <int> (floor(position.x));
            hitbox.y = static_cast <int> (floor(position.y));
        }
};
