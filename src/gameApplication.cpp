//debugging
#include <iostream>
#include <cmath>

// accurately timing the main loop execution
#include <chrono>
#include <thread>

// interface with display drivers, also some game-related features
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

            for (int i = 0; i < physicsSubsteps; i++)
            {
                tick(delta.count() / (double) physicsSubsteps);
            }

            draw();

            int accuracy = (int) (targetRefreshTime.count() * 0.000001 - delta.count()) * 100;
            for (int i = 0; i < accuracy; i++)
            {
                cout << " ";
            }
            cout << "|" << endl;
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
    array<bool, 7> inputArray;

    int mouseX, mouseY;

    Player player;

    int physicsSubsteps = 10;

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

        for (int i = 0; i < 7; i++) inputArray[i] = false;
        keyboardState = SDL_GetKeyboardState(NULL);
    }

    void initializePlayer()
    {}

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

        for (int i = 0; i < 7; i++) inputArray[i] = false;

        if (keyboardState[SDL_SCANCODE_UP]) inputArray[0] = true;
        if (keyboardState[SDL_SCANCODE_RIGHT]) inputArray[1] = true;
        if (keyboardState[SDL_SCANCODE_DOWN]) inputArray[2] = true;
        if (keyboardState[SDL_SCANCODE_LEFT]) inputArray[3] = true;

        if (SDL_GetMouseState(&mouseX, &mouseY))
        {}

        player.updateInputs(inputArray);
    }

    void tick(double delta)
    {
        player.tick(delta);
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
