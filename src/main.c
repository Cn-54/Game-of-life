#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>

#define WIDTH 80
#define HEIGHT 60
#define CELL_SIZE 10

int grid[WIDTH][HEIGHT];
int next_grid[WIDTH][HEIGHT];

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

    // set grid to next grid
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            grid[x][y] = next_grid[x][y];
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


void handle_mouse(SDL_Event *event)
{
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

        int grid_x = event->button.x / CELL_SIZE;
        int grid_y = event->button.y / CELL_SIZE;

        grid[grid_x][grid_y] = !grid[grid_x][grid_y];
    }
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
    int paused = 1;

    while (running) {

        // Handle events
        while (SDL_PollEvent(&event)) {

            // Close button
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }

            if(event.type == SDL_EVENT_KEY_DOWN) {
                if(event.key.key == SDLK_SPACE) {
                    paused = !paused;
                }
            }

            handle_mouse(&event);
        }

        // MAIN LOOP CODE HERE
        
        if (!paused) {
            update_grid();
        }

        draw_grid(renderer);
        SDL_Delay(16);

    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}