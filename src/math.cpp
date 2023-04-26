double clamp(double n, double min, double max)
{
    if (n >= max)
        return max;
    if (n <= min)
        return min;
    return n;
}

bool hasIntersectionF(SDL_FRect *rectA, SDL_FRect *rectB)
{
    if (
        (
            rectB->x < rectA->x + rectA->w and
            rectB->x + rectB->w > rectA->x) and
        (rectB->y < rectA->y + rectA->h and
         rectB->y + rectB->h > rectA->y))
    {
        return true;
    }
    return false;
}

bool intersectRectF(SDL_FRect *rectA, SDL_FRect *rectB, SDL_FRect *intersectRect)
{
    if (not hasIntersectionF(rectA, rectB))
        return false;

    if (rectB->x > rectA->x)
    {
        intersectRect->x = rectB->x;
        intersectRect->w = min(rectA->w - (rectB->x - rectA->x), rectB->w);
    }
    else
    {
        intersectRect->x = rectA->x;
        intersectRect->w = min(rectB->w - (rectA->x - rectB->x), rectA->w);
    }
    if (rectB->y > rectA->y)
    {
        intersectRect->y = rectB->y;
        intersectRect->h = min(rectA->h - (rectB->y - rectA->y), rectB->h);
    }
    else
    {
        intersectRect->y = rectA->y;
        intersectRect->h = min(rectB->h - (rectA->y - rectB->y), rectA->h);
    }
    return true;
}
