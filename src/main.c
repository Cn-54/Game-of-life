#include <SDL3/SDL.h>

int main(void)
{
    // Initialise SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "SDL Test",
        800,
        600,
        0
    );

    if (window == NULL) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == NULL) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop and event handler
    SDL_Event event;
    int running = 1;

    while (running) {

        // Handle events
        while (SDL_PollEvent(&event)) {

            // Close button
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        // MAIN LOOP CODE HERE


        // Present renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}