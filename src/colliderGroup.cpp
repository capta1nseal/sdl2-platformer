class ColliderGroup
{
public:
    ColliderGroup()
    {
        colliderCount = 1;
        colliders.reserve(colliderCount);
        colliders[0] = RectCollider(-100, 500, 200, 50);
    }

    vector<RectCollider> getColliders()
    {
        return colliders;
    }

    vector<RectCollider> getOverlappedColliders(SDL_Rect *rect)
    {
        vector<RectCollider> returnRects;
        returnRects.reserve(colliderCount);
        int actualIndex = 0;
        for (int i = 0; i < colliderCount; i++)
        {
            if (SDL_HasIntersection(rect, colliders[i].getRect()))
            {
                returnRects[actualIndex] = colliders[i];
                actualIndex += 1;
            }
        }
        returnRects.resize(actualIndex + 1);
        return returnRects;
    }
private:
    vector<RectCollider> colliders;
    size_t colliderCount;
};
