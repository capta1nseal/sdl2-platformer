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

            airResistance = 0.0002;
            surfaceFriction = 0.01;

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
            jumping = false;
            if (input->jumpPressed() and onGround) // Z - jump
            {
                velocity.x *= jumpFriction;
                velocity.y -= jumpVelocity;
                jumping = true;
            }
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

            acceleration.scale(delta);

            acceleration.add(scaleVec2(velocity, -1 * airResistance));

            if (onGround)
            {
                acceleration.x -= velocity.x * surfaceFriction;
            }

            velocity.add(acceleration);

            acceleration.zero();

            previousPosition.set(position);

            position.add(scaleVec2(velocity, delta));

            onGround = false;

            if (position.y > 1080 - hitbox.w)
            {
                velocity.y = 0.0;
                position.y = 1080.0 - hitbox.w;
                onGround = true;
            }

            updateHitboxPosition();
        }

        void draw(SDL_Renderer *renderer, Camera *camera)
        {
            Vec2 cameraPosition = camera->getPosition(); 
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_FRect drawRect;
            drawRect.x = hitbox.x - cameraPosition.x;
            drawRect.y = hitbox.y - cameraPosition.y;
            drawRect.w = hitbox.w;
            drawRect.h = hitbox.h;
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

        SDL_FRect hitbox;

        Input *input;

        void updateHitboxPosition()
        {
            hitbox.x = position.x;
            hitbox.y = position.y;
        }
};
