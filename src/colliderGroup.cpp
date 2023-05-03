class ColliderGroup
{
public:
    ColliderGroup()
    {
        colliderCount = 100 * 100;
        colliders.reserve(colliderCount);
        int x = -500;
        int y = 1000;
        int w = 1000;
        int h = 100;
        for (int j = 0; j < 100; j++)
        {
            x = -500 + 50 * j;
            y = 1000 + j * 200;
            for (int i = 0; i < 100; i++)
            {
                colliders.push_back(RectCollider(x, y, w, h));
                x += 1200;
                y += 100;
            }
        }
        std::cout << colliderCount << std::endl << colliders.size() << std::endl;
    }

    std::vector<SDL_FRect *> getOverlappedColliders(SDL_FRect *rect)
    {
        std::vector<SDL_FRect *> returnRects;
        returnRects.reserve(colliderCount);
        int actualIndex = 0;
        for (int i = 0; i < colliderCount; i++)
        {
            if (hasIntersectionF(rect, colliders[i].getRect()))
            {
                returnRects.push_back(colliders[i].getRect());
                actualIndex += 1;
            }
        }
        returnRects.resize(actualIndex);
        return returnRects;
    }

    void draw(SDL_Renderer *renderer, Camera *camera)
    {
        for (int i = 0; i < colliderCount; i++)
        {
            colliders[i].draw(renderer, camera);
        }
    }
private:
    std::vector<RectCollider> colliders;
    size_t colliderCount;
};
