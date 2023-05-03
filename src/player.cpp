class Player
{
public:
    Player()
    {
        gravityVector.y = 4000;

        walkAcceleration = 5000;
        jumpVelocity = 1000;
        jumpFriction = 0.85;

        jumpBonus = 5.0;
        airControl = 0.1;

        airResistance = 0.2;
        surfaceFriction = 6.0;

        playerWidth = 32;
        playerHeight = 32;

        hitbox.w = playerWidth;
        hitbox.h = playerHeight;
        updateHitboxPosition();

        onGround = false;
        jumping = false;
    }

    void setInput(Input *inputPtr)
    {
        input = inputPtr;
    }

    void tick(double delta, Level *level)
    {
        if (input->jumpPressed() and onGround) // Z - jump
        {
            velocity.x *= jumpFriction;
            velocity.y -= jumpVelocity;
            jumping = true;
        }
        else
            jumping = false;
        if (input->rightPressed()) // right arrow
        {
            if (jumping)
                acceleration.x += walkAcceleration * jumpBonus;
            else if (onGround)
                acceleration.x += walkAcceleration;
            else
                acceleration.x += walkAcceleration * airControl;
        }
        if (input->leftPressed()) // left arrow
        {
            if (jumping)
                acceleration.x -= walkAcceleration * jumpBonus;
            else if (onGround)
                acceleration.x -= walkAcceleration;
            else
                acceleration.x -= walkAcceleration * airControl;
        }

        acceleration.add(&gravityVector);

        acceleration.subtract(scaleVec2(&velocity, airResistance));

        if (onGround)
        {
            acceleration.x -= velocity.x * surfaceFriction;
        }

        acceleration.scale(delta);

        velocity.add(&acceleration);

        acceleration.zero();

        previousPosition.set(&position);

        position.add(scaleVec2(&velocity, delta));
        updateHitboxPosition();

        onGround = false;
        
        std::vector<SDL_FRect *> collideRects = level->getOverlappedColliders(&hitbox);
        for (int i = 0; i < collideRects.size(); i++)
        {
            collideRect(collideRects[i], delta);
        }
        

        updateHitboxPosition();
    }

    void draw(SDL_Renderer *renderer, Camera *camera)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawPosition.set(camera->mapCoordinate(&position));
        double drawScale = camera->getScale();
        drawRect.x = drawPosition.x;
        drawRect.y = drawPosition.y;
        drawRect.w = playerWidth * drawScale;
        drawRect.h = playerHeight * drawScale;
        SDL_RenderFillRectF(renderer, &drawRect);
    }

    Vec2 getCentre()
    {
        return addVec2(&position, Vec2(hitbox.w * 0.5, hitbox.h * 0.5));
    }

    SDL_FRect *getRect()
    {
        return &hitbox;
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

    int playerWidth = 32;
    int playerHeight = 32;

    SDL_FRect hitbox;
    SDL_FRect collisionRect;

    Input *input;

    Vec2 drawPosition;
    SDL_FRect drawRect;

    void updateHitboxPosition()
    {
        hitbox.x = position.x;
        hitbox.y = position.y;
    }

    void collideRect(SDL_FRect *rect, double delta)
    {
        if (intersectRectF(&hitbox, rect, &collisionRect))
        {
            if (collisionRect.w >= collisionRect.h)
            {
                if (velocity.y == 0)
                {
                }
                else if (velocity.y > 0)
                {
                    position.y = rect->y - playerHeight;
                    onGround = true;
                }
                else
                {
                    position.y = rect->y + rect->h;
                }
                velocity.y = 0.0;
            }
            else
            {
                if (velocity.x == 0)
                {
                }
                else if (velocity.x > 0)
                {
                    position.x = rect->x - playerWidth;
                }
                else
                {
                    position.x = rect->x + rect->w;
                }
                velocity.x = 0.0;
            }
            updateHitboxPosition();
        }
    }
};
