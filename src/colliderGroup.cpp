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
        int h = 100000;
        for (int i = 0; i < colliderCount; i++)
        {
            colliders.push_back(RectCollider(x, y, w, h));
            x += 1100;
            y -= 100;
        }
        cout << colliderCount << endl << colliders.size() << endl;
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
    vector<RectCollider> colliders;
    size_t colliderCount;
};
