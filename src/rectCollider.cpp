class RectCollider
{
public:
    RectCollider()
    {}

    RectCollider(Vec2 initPosition, Vec2 initSize)
    {
        hitbox.x = initPosition.x;
        hitbox.y = initPosition.y;
        hitbox.w = initSize.x;
        hitbox.h = initSize.y;

        colour.r = 0;
        colour.g = 255;
        colour.b = 0;
        colour.a = 255;
    }

    RectCollider(int x, int y, int w, int h)
    {
        hitbox.x = x;
        hitbox.y = y;
        hitbox.w = w;
        hitbox.h = h;

        colour.r = 0;
        colour.g = 255;
        colour.b = 0;
        colour.a = 255;
    }

    SDL_Rect *getRect()
    {
        return &hitbox;
    }

    void draw(SDL_Renderer *renderer, Camera* camera)
    {
        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_FRect drawRect;
        Vec2 drawPosition = camera->mapCoordinate(Vec2(hitbox.x, hitbox.y));
        double drawScale = camera->getScale();
        drawRect.x = drawPosition.x;
        drawRect.y = drawPosition.y;
        drawRect.w = hitbox.w * drawScale;
        drawRect.h = hitbox.h * drawScale;
        SDL_RenderFillRectF(renderer, &drawRect);
    }
private:
    SDL_Rect hitbox;
    SDL_Colour colour;
};
