// debugging
#include <iostream>

// math. possibly unused.
#include <cmath>

// accurately timing the main loop execution
#include <chrono>
#include <thread>

// input array
#include <array>

using namespace std;

// interface with display drivers, also some game-related features
#include <SDL2/SDL.h>

// some useful mathematical functions
#include "math.cpp"

// class for 2D vectors and operations
#include "vec2.cpp"

// class for holding and getting input state
#include "input.cpp"

// class for camera positioning and scaling
#include "camera.cpp"

// class for player, includes controls, physics and drawing
#include "player.cpp"

// class for an axis-aligned bounding box collider
#include "rectCollider.cpp"


chrono::_V2::steady_clock::time_point now()
{
    return chrono::steady_clock::now();
}


class Game
{
public:
    Game(double initialFramerate = 60.0)
      : framerate(initialFramerate)
    {
        initializeSdl();
        initializeInput();
        initializeColliders();
        initializePlayer();
        initializeCamera();
    }

    void run()
    {
        using chrono::operator""us;

        const chrono::duration<double, micro> targetRefreshTime = 1000000.0us / framerate;
        chrono::time_point<chrono::_V2::steady_clock, chrono::duration<double, chrono::_V2::steady_clock::period>> start;
        chrono::duration<double, micro> waitPeriod = targetRefreshTime;
        chrono::time_point<chrono::_V2::steady_clock, chrono::duration<double, chrono::_V2::steady_clock::period>> nextTime;
        
        chrono::duration<double> delta;

        const int tuningIterations = (int) floor(framerate);
        int tuningIterator = 0;
        auto tuningPeriodStart = now();
 
        running = true;
        draw();
        while (running)
        {
            start = now();
            nextTime = start + waitPeriod;

            tuningIterator++;
            if (tuningIterator == tuningIterations)
            {
                waitPeriod += targetRefreshTime - (now() - tuningPeriodStart) / tuningIterations;
                tuningIterator = 0;
                tuningPeriodStart = now();
            }
            handleEvents();

            tick(delta.count());

            draw();
            
            this_thread::sleep_until(nextTime);
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

    int physicsSubsteps = 10;

    Camera camera;

    void initializeSdl()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GetCurrentDisplayMode(0, &displayMode);

        displayWidth = displayMode.w;
        displayHeight = displayMode.h;

        window = SDL_CreateWindow(
            "sdl-2d-game",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            displayWidth, displayHeight,
            SDL_WINDOW_FULLSCREEN_DESKTOP);

        Uint32 renderFlags = SDL_RENDERER_ACCELERATED;
        renderer = SDL_CreateRenderer(window, -1, renderFlags);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(renderer);

        keyboardState = SDL_GetKeyboardState(NULL);
    }

    void initializeInput()
    {
        input.setKeyboardState(keyboardState);
    }

    void initializeColliders()
    {
        
    }

    void initializePlayer()
    {
        player.setInput(&input);
    }

    void initializeCamera()
    {
        camera.setInput(&input);

        camera.initializeResolution(displayWidth, displayHeight);
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

        if (SDL_GetMouseState(&mouseX, &mouseY)) {}
    }

    void tick(double delta)
    {
        for (int i = 0; i < physicsSubsteps; i++)
        {
            player.tick(delta / (double) physicsSubsteps);
        }

        camera.setTargetPosition(player.getCentre());
        camera.tick(delta);
    }

    void draw()
    {
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, NULL);

        player.draw(renderer, &camera);

        SDL_Rect centre;
        centre.x = static_cast<int>(floor(displayWidth / 2.0) - 1);
        centre.y = static_cast<int>(floor(displayHeight / 2.0) - 1);
        centre.w = 2;
        centre.h = 2;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &centre);

        SDL_RenderPresent(renderer);
    }
};
