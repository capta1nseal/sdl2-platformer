class Player
{
    public:
        Player()
        {
            gravityVector.y = 4000;

            walkAcceleration = 4000;
            jumpVelocity = 1000;
            jumpFriction = 0.85;

            jumpBonus = 5.0;
            airControl = 0.1;

            airResistance = 0.05;
            surfaceFriction = 2.5;

            hitbox.w = 32;
            hitbox.h = 32;
            updateHitboxPosition();

            onGround = false;
            jumping = false;
        }

        void setInput(Input *inputPtr)
        {
            input = inputPtr;
        }

        void tick(double delta)
        {
            if (input->jumpPressed() and onGround) // Z - jump
            {
                velocity.x *= jumpFriction;
                velocity.y -= jumpVelocity;
                jumping = true;
            } else jumping = false;
            if (input->rightPressed()) // right arrow
            {
                if (jumping) acceleration.x += walkAcceleration * jumpBonus;
                else if (onGround) acceleration.x += walkAcceleration;
                else acceleration.x += walkAcceleration * airControl;
            }
            if (input->leftPressed()) // left arrow
            {
                if (jumping) acceleration.x -= walkAcceleration * jumpBonus;
                else if (onGround) acceleration.x -= walkAcceleration;
                else acceleration.x -= walkAcceleration * airControl;
            }

            acceleration.add(gravityVector);

            acceleration.add(scaleVec2(velocity, -1 * airResistance));

            if (onGround)
            {
                acceleration.x -= velocity.x * surfaceFriction;
            }

            acceleration.scale(delta);

            velocity.add(acceleration);

            acceleration.zero();

            previousPosition.set(position);

            position.add(scaleVec2(velocity, delta));

            onGround = false;

            if (position.y > 500 - hitbox.w)
            {
                velocity.y = 0.0;
                position.y = 500.0 - hitbox.w;
                onGround = true;
            }

            updateHitboxPosition();
        }

        void draw(SDL_Renderer *renderer, Camera *camera)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_FRect drawRect;
            Vec2 drawPosition = camera->mapCoordinate(position);
            double drawScale = camera->getScale();
            drawRect.x = drawPosition.x;
            drawRect.y = drawPosition.y;
            drawRect.w = hitbox.w * drawScale;
            drawRect.h = hitbox.h * drawScale;
            SDL_RenderFillRectF(renderer, &drawRect);
        }

        Vec2 getCentre()
        {
            return addVec2(position, Vec2(hitbox.w * 0.5, hitbox.h * 0.5));
        }

    private:
        Vec2 position;
        Vec2 previousPosition;
        Vec2 velocity;
        Vec2 acceleration;
        Vec2 gravityVector;

        bool onGround;
        bool jumping;

        double walkAcceleration; 
        double jumpVelocity;
        double jumpFriction;

        double jumpBonus;
        double airControl;

        double airResistance;
        double surfaceFriction;

        SDL_Rect hitbox;
        SDL_Rect collisionRect;

        Input *input;

        void updateHitboxPosition()
        {
            hitbox.x = position.x;
            hitbox.y = position.y;
        }

        void collideRect(SDL_Rect *rect)
        {
            if (SDL_IntersectRect(&hitbox, rect, &collisionRect))
            {
                if (abs(collisionRect.y * velocity.y) >= abs(collisionRect.x * velocity.x))
                {
                    velocity.y = 0;
                    if (velocity.y >= 0)
                    {
                        position.y -= collisionRect.y;
                    }
                    else
                    {
                        position.y += collisionRect.x;
                    }
                }
                else
                {
                    velocity.x = 0;
                    if (velocity.x >= 0)
                    {
                        position.x -= collisionRect.x;
                    }
                    else
                    {
                        position.x += collisionRect.x;
                    }
                }
            }
        }
};
