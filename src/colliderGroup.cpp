class ColliderGroup
{
public:
    ColliderGroup()
    {
        colliderCount = 100;
        colliders.reserve(colliderCount);
        int x = -500;
        int y = 1000;
        int w = 1000;
        int h = 10000;
        for (int i = 0; i < colliderCount; i++)
        {
            colliders.push_back(RectCollider(x, y, w, h));
            x += 1100;
            y -= 75;
        }
        cout << colliderCount << endl << colliders.size() << endl;
    }

    vector<SDL_FRect *> getOverlappedColliders(SDL_FRect *rect)
    {
        vector<SDL_FRect *> returnRects;
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

    SDL_FRect *getTestCollider()
    {
        return colliders[0].getRect();
    }

    void draw(SDL_Renderer *renderer, Camera *camera)
    {
        for (int i = 0; i < colliderCount; i++)
        {
            colliders[i].draw(renderer, camera);
        }
    }
private:
    vector<RectCollider> colliders;
    size_t colliderCount;
};
