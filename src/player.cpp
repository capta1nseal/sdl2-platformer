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

        airResistance = 0.2;
        surfaceFriction = 5.0;

        playerWidth = 32;
        playerHeight = 32;

        hitbox.w = playerWidth + 2;
        hitbox.h = playerHeight + 2;
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

        updateHitboxPosition();

        // collideRect(level->getTestCollider());

        
        vector<SDL_Rect *> collideRects = level->getOverlappedColliders(&hitbox);
        for (int i = 0; i < collideRects.size(); i++)
        {
            collideRect(collideRects[i]);
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
        drawRect.w = playerWidth * drawScale;
        drawRect.h = playerHeight * drawScale;
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

    int playerWidth = 32;
    int playerHeight = 32;

    SDL_Rect hitbox;
    SDL_Rect collisionRect;

    Input *input;

    void updateHitboxPosition()
    {
        hitbox.x = position.x - 1;
        hitbox.y = position.y - 1;
    }

    void collideRect(SDL_Rect *rect)
    {
        if (SDL_IntersectRect(&hitbox, rect, &collisionRect))
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
