#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#define WIDTH 80
#define HEIGHT 60
#define CELL_SIZE 10

int grid[HEIGHT][WIDTH];
int next_grid[HEIGHT][WIDTH];

int count_neighbours(int x, int y)
{
    int count = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (dx == 0 && dy == 0)
                continue;

            int nx = (x + dx + WIDTH) % WIDTH;
            int ny = (y + dy + HEIGHT) % HEIGHT;

            count += grid[nx][ny];
        }
    }

    return count;
}

void update_grid(){
    for(int x = 0;x < WIDTH;x++){
       for(int y = 0;y < HEIGHT;y++){
            // count neighbours
            int count = count_neighbours( x,  y);

            // update grid based on neighbour count
            if (grid[x][y] == 1) {
                if (count == 2 || count == 3) {
                    next_grid[x][y] = 1;
                } else {
                    next_grid[x][y] = 0;
                }
            } else {
                if (count == 3) {
                    next_grid[x][y] = 1;
                } else {
                    next_grid[x][y] = 0;
                }
            }
        }
    }
}

void draw_grid(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            if (grid[x][y] == 1) {

                SDL_FRect cell = {
                    x * CELL_SIZE,
                    y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

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
        
        update_grid();

        draw_grid(renderer);

        // 
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}