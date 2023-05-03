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

    std::vector<SDL_FRect *> getOverlappedColliders(SDL_FRect *rect)
    {
        return colliders.getOverlappedColliders(rect);
    }

private:
    const char *path;
    ColliderGroup colliders;
};
