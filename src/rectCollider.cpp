class RectCollider
{
public:
    RectCollider(Vec2 initPosition, Vec2 initSize)
    {
        rect.x = initPosition.x;
        rect.y = initPosition.y;
        rect.w = initSize.x;
        rect.h = initSize.y;
    }

    SDL_FRect getRect()
    {
        return rect;
    }
private:
    SDL_FRect rect;
};
