#define SDL_MAIN_HANDLED

#include <list>
#include <memory>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Snake.h"
#include "Consumable.h"
#include "Apple.h"

#include "Constants.h"
#include "Renderer.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Snake snake;
    std::list<std::shared_ptr<Consumable>> consumables;
} Game;

int main() {
    Game game;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    const SDL_Color Black = {0, 0, 0, 255};
    TTF_Font* font = loadFont("Roboto-Regular", 24);

    game.window = SDL_CreateWindow("SDL2 Window",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);

    game.snake = Snake();
    game.consumables = std::list<std::shared_ptr<Consumable>>();

    SDL_Event event;
    bool isRunning = true;

    Uint32 lastFrameTime = SDL_GetTicks();
    Uint32 frameCount = 0;
    Uint32 fpsLastTime = SDL_GetTicks(); // For FPS counter
    Uint32 fps = 0;
    float accumulatedTime = 0.0f;

    while (isRunning) {
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f; // in seconds
        lastFrameTime = currentFrameTime;

        accumulatedTime += deltaTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }

            // Input
            {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP: {
                            game.snake.changeDirection(Direction::UP);
                            break;
                        }
                        case SDLK_DOWN: {
                            game.snake.changeDirection(Direction::DOWN);
                            break;
                        }
                        case SDLK_LEFT: {
                            game.snake.changeDirection(Direction::LEFT);
                            break;
                        }
                        case SDLK_RIGHT: {
                            game.snake.changeDirection(Direction::RIGHT);
                            break;
                        }
                    }
                }
            }
        }

        // Update
        {
            while (accumulatedTime >= UPDATE_INTERVAL) {
                game.snake.update(game.consumables);

                for (const auto& item : game.consumables) {
                    item->update(game.consumables);
                }

                // spawn consumables based on the snake's length and the number of consumables but at random intervals
                if (game.consumables.size() < game.snake.getTailLength() + 1 / 2 || game.consumables.empty()) {
                    auto item = new Apple(game.renderer); // TODO: Use inheritance to create different types of consumables
                    item->spawn(game.consumables, [&game](int x, int y) {
                        return game.snake.isSnake(x, y);
                    });
                }

                accumulatedTime -= UPDATE_INTERVAL;
            }
        }

        // Render
        {
            SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);
            SDL_RenderClear(game.renderer);

            game.snake.draw(game.renderer);
            for (const auto& item: game.consumables) {
                item->draw(game.renderer);
            }

            std::string fpsStr = "FPS: " + std::to_string(fps);
            drawText(game.renderer, font, fpsStr.c_str(), 10, 10, Black);

            SDL_RenderPresent(game.renderer);
        }

        // Frame rate limiting
        {
            Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
            if (frameTime < FRAME_TIME_MS) {
                SDL_Delay(FRAME_TIME_MS - frameTime);
            }

            frameCount++;
            if (SDL_GetTicks() - fpsLastTime >= 1000) { // If it's been a second since last check
                fps = frameCount - 1;
                frameCount = 0;
                fpsLastTime = SDL_GetTicks();
            }
        }
    }

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
