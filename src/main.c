#include <SDL3/SDL.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    // create window
    SDL_Window *window = SDL_CreateWindow(
        "SDL Test",
        800,
        600,
        0
    );

    // create renderer
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, NULL);

    
        // create main loop and event handler
    SDL_Event event;
    int running = 1;

    while (running) {

        // close button
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        // MAIN LOOP CODE HERE


        //
    }

    // close window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}