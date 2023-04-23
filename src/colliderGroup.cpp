class ColliderGroup
{
public:
    ColliderGroup()
    {
        colliderCount = 1;
        colliders.reserve(colliderCount);
        colliders[0] = RectCollider(-250, 500, 500, 100);
    }

    vector<SDL_Rect *> getOverlappedColliders(SDL_Rect *rect)
    {
        vector<SDL_Rect *> returnRects;
        returnRects.reserve(colliderCount);
        int actualIndex = 0;
        for (int i = 0; i < colliderCount; i++)
        {
            if (SDL_HasIntersection(rect, colliders[i].getRect()))
            {
                returnRects.emplace_back(colliders[i].getRect());
                actualIndex += 1;
            }
        }
        returnRects.resize(actualIndex + 1);
        return returnRects;
    }

    SDL_Rect *getTestCollider()
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
