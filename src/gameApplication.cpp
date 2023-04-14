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

auto now()
{
    return chrono::steady_clock::now();
}

class Game
{
public:
    Game(double framerate = 60.0)
    {
        initializeSdl();
        initializePlayer();
    }

    void run()
    {
        using chrono::operator""us;

        const double framerate = 60.0;
        const chrono::duration<double, micro> target_refresh_time = 1000000.0us / framerate;
        cout << 1000000.0 / framerate << endl;

        auto start = now();
        auto wait_period = target_refresh_time;
        auto next_time = start + wait_period;
        chrono::duration<double, micro> elapsed = wait_period;

        const int tuning_iterations = 10;
        int tuning_iterator = 0;
        auto tuning_period_start = now();
 
        running = true;
        draw();
        while (running)
        {
            start = now();
            next_time = start + wait_period;

            cout << elapsed.count() << endl;
            tuning_iterator++;
            if (tuning_iterator == tuning_iterations)
            {
                wait_period += target_refresh_time - (now() - tuning_period_start) / tuning_iterations;
                tuning_iterator = 0;
                tuning_period_start = now();
            }
            handleEvents();

            tick();

            draw();

            this_thread::sleep_until(next_time);
            elapsed = now() - start;
        }
    }

private:
    bool running;
    int displayWidth, displayHeight;

    SDL_DisplayMode DisplayMode;
    SDL_Window *window;
    SDL_Renderer *renderer;

    double framerate;

    SDL_Event event;

    int mouseX, mouseY;

    void initializeSdl()
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        int diplay_count = SDL_GetNumVideoDisplays();

        SDL_GetCurrentDisplayMode(1, &DisplayMode);

        displayWidth = DisplayMode.w;
        displayHeight = DisplayMode.h;

        window = SDL_CreateWindow(
            "sdl-2d-game",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            displayWidth, displayHeight,
            SDL_WINDOW_FULLSCREEN_DESKTOP);

        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        renderer = SDL_CreateRenderer(window, -1, render_flags);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(renderer);
    }

    void initializePlayer()
    {
        SDL_Colour playerColour = SDL_Colour();
        playerColour.r = 255;
        playerColour.g = 255;
        playerColour.b = 255;
        playerColour.a = 255;

        Player player = Player(playerColour);
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
        cout << "tick" << endl;
    }

    void draw()
    {
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, NULL);

        SDL_RenderPresent(renderer);
    }
};
