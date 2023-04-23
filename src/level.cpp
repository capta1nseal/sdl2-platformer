class Level
{
public:
    Level()
    {
        testCollider = RectCollider(-100, 500, 200, 50);
    }

    Level(const char *loadPath)
      : path(loadPath)
    {
        testCollider = RectCollider(-100, 500, 200, 50);
    }

    void drawColliders(SDL_Renderer *renderer, Camera *camera)
    {
        testCollider.draw(renderer, camera);
    }
private:
    const char *path;
    RectCollider testCollider;
};
