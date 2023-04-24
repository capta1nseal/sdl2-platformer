class Level
{
public:
    Level()
    {
    }

    Level(const char *loadPath)
        : path(loadPath)
    {
    }

    void drawColliders(SDL_Renderer *renderer, Camera *camera)
    {
        colliders.draw(renderer, camera);
    }

    vector<SDL_Rect *> getOverlappedColliders(SDL_Rect *rect)
    {
        return colliders.getOverlappedColliders(rect);
    }

    SDL_Rect *getTestCollider()
    {
        return colliders.getTestCollider();
    }

private:
    const char *path;
    ColliderGroup colliders;
};
