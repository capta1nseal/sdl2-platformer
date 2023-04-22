class RectCollider
{
public:
    RectCollider(Vec2 initPosition, Vec2 initSize)
    {
        rect.x = initPosition.x;
        rect.y = initPosition.y;
        rect.w = initSize.x;
        rect.h = initSize.y;

        colour.r = 0;
        colour.g = 255;
        colour.b = 0;
        colour.a = 0;
    }

    SDL_FRect getRect()
    {
        return rect;
    }

    void draw(SDL_Renderer *renderer, Camera* camera)
    {
        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_FRect drawRect;
        Vec2 drawPosition = camera->mapCoordinate(Vec2(rect.x, rect.y));
        double drawScale = camera->getScale();
        drawRect.x = drawPosition.x;
        drawRect.y = drawPosition.y;
        drawRect.w = rect.w * drawScale;
        drawRect.h = rect.h * drawScale;
    }
private:
    SDL_FRect rect;
    SDL_Colour colour;
};
