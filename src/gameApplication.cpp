// mainly used for debugging, should be removed for the final build
#include <iostream>

// chrono and thread used for accurately timing the main loop execution
#include <chrono>
#include <thread>

// used for SDL2 displays
#include <vector>

// SDL2 is used to interface with the display drivers, also used for some game-related features
#include <SDL2/SDL.h>

// class for player, includes controls, physics and drawing
#include "player.cpp"

using namespace std;

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
        initializePlayer();
    }

    void run()
    {
        using chrono::operator""us;

        const chrono::duration<double, micro> targetRefreshTime = 1000000.0us / framerate;
        chrono::duration<double, micro> waitPeriod = targetRefreshTime;
        chrono::time_point<chrono::_V2::steady_clock, chrono::duration<double, chrono::_V2::steady_clock::period>> nextTime;

        const int tuningIterations = (int) floor(framerate);
        int tuningIterator = 0;
        auto tuningPeriodStart = now();
 
        running = true;
        draw();
        while (running)
        {
            nextTime = now() + waitPeriod;

            tuningIterator++;
            if (tuningIterator == tuningIterations)
            {
                waitPeriod += targetRefreshTime - (now() - tuningPeriodStart) / tuningIterations;
                tuningIterator = 0;
                tuningPeriodStart = now();
            }
            handleEvents();

            tick();

            draw();

            this_thread::sleep_until(nextTime);
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

    int mouseX, mouseY;

    Player player;

    void initializeSdl()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        int displayCount = SDL_GetNumVideoDisplays();
        SDL_Rect displayBounds;
        int displayIndexUnderCursor;

        for (int i = 0; i < displayCount; i++)
        {
            SDL_GetDisplayBounds(i, &displayBounds);
        }

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
    }

    void initializePlayer()
    {
        cout << "initializing player" << endl;
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

        if (SDL_GetMouseState(&mouseX, &mouseY))
        {
            cout << "mouse event at (" << mouseX << "," << mouseY << ")" << endl;
        }
    }

    void tick()
    {
        player.tick();
    }

    void draw()
    {
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, NULL);

        player.draw(renderer);

        SDL_RenderPresent(renderer);
    }
};
