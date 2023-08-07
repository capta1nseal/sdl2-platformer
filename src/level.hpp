#ifndef _SDL2PLEVEL_
#define _SDL2PLEVEL_

#include <vector>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

#include "camera.hpp"
#include "colliderGroup.hpp"

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

#endif
