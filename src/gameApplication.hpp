#ifndef _SDL2PGAMEAPPLICATION_
#define _SDL2PGAMEAPPLICATION_

// debugging
#include <iostream>

// accurately timing loop execution and multithreading
#include <chrono>
#include <thread>

// interface with display drivers, also some game-related features
#include <SDL2/SDL.h>

// class for 2D vectors and operations
#include "vec2.hpp"

// some useful mathematical functions
#include "math.hpp"

// class for holding and getting input state
#include "input.hpp"

// class for camera positioning and scaling
#include "camera.hpp"

// class for an axis-aligned bounding box collider
#include "rectCollider.hpp"

// class for grouping and interacting with colliders
#include "colliderGroup.hpp"

// class for storing a level's colliders and art during runtime
#include "level.hpp"

// class for player, includes controls, physics and drawing
#include "player.hpp"

std::chrono::_V2::steady_clock::time_point now()
{
    return std::chrono::steady_clock::now();
}

class Game
{
public:
    Game(double initialFramerate = 60.0)
        : framerate(initialFramerate)
    {
        initializeSdl();
        initializeInput();
        initializeLevel();
        initializePlayer();
        initializeCamera();
    }

    void run()
    {
        using std::chrono::operator""us;

        const std::chrono::duration<double, std::micro> targetRefreshTime = 1000000.0us / framerate;
        std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double, std::chrono::_V2::steady_clock::period>> start;
        std::chrono::duration<double, std::micro> waitPeriod = targetRefreshTime;
        std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<double, std::chrono::_V2::steady_clock::period>> nextTime;

        std::chrono::duration<double> delta;

        const int tuningIterations = (int)floor(framerate);
        int tuningIterator = 0;
        auto tuningPeriodStart = now();

        running = true;
        draw();
        while (running)
        {
            start = now();
            // nextTime = start + waitPeriod;

            // tuningIterator++;
            // if (tuningIterator == tuningIterations)
            // {
            //     waitPeriod += targetRefreshTime - (now() - tuningPeriodStart) / tuningIterations;
            //     tuningIterator = 0;
            //     tuningPeriodStart = now();
            // }
            handleEvents();

            tick(delta.count());

            std::cout << delta.count() << '\n';

            draw();

            // std::this_thread::sleep_until(nextTime);
            delta = now() - start;
        }
    }

private:
    bool running;
    int displayWidth, displayHeight;

    SDL_DisplayMode displayMode;
    SDL_Window *window;
    SDL_Renderer *renderer;

    double framerate;

    SDL_Event event;
    const Uint8 *keyboardState;

    int mouseX, mouseY;

    Input input;

    Player player;

    int physicsSubsteps = 100; // to make up for inaccurate modelling on lower deltas

    Camera camera;

    Level level;

    void initializeSdl()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GetCurrentDisplayMode(0, &displayMode);

        displayWidth = displayMode.w;
        displayHeight = displayMode.h;

        Uint32 windowFlags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        window = SDL_CreateWindow(
            "sdl-platformer",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            displayWidth, displayHeight,
            windowFlags);

        Uint32 renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        renderer = SDL_CreateRenderer(window, -1, renderFlags);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        keyboardState = SDL_GetKeyboardState(NULL);
    }

    void initializeInput()
    {
        input.setKeyboardState(keyboardState);
    }

    void initializeLevel()
    {
        level = Level("data/levels/0");
    }

    void initializePlayer()
    {
        player.setInput(&input);
    }

    void initializeCamera()
    {
        camera.setInput(&input);

        camera.setFollowRect(player.getRect());

        camera.initializeResolution(displayWidth, displayHeight);
        camera.setMode(1);
        camera.setPosition(player.getCentre());
    }

    void handleEvents()
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
                }
            }
        }

        SDL_PumpEvents();

        input.updateInputs();

        if (SDL_GetMouseState(&mouseX, &mouseY))
        {
        }
    }

    void tick(double delta)
    {
        for (int i = 0; i < physicsSubsteps; i++)
        {
            player.tick(delta / (double)physicsSubsteps, &level);
        }

        camera.tick(delta);
    }

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        level.drawColliders(renderer, &camera);

        player.draw(renderer, &camera);

        SDL_RenderPresent(renderer);
    }
};

#endif
