#include <algorithm>
#include "Snake.h"

void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Snake::Snake() {
    reset();
}

bool Snake::isSnake(int pX, int pY) {
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == pX && tailY[i] == pY) {
            return true;
        }
    }

    return pX == this->x && pY == this->y;
}

void Snake::extendTail() {
    if (tailLength < 100) {
        tailLength++;
    }

    justAte = true;
}

void Snake::update(std::list<std::shared_ptr<Consumable>>& consumables) {
    // Store the previous position of the head
    int prevX = x;
    int prevY = y;

    // Update the tail
    {
        if (dir != Direction::STOP) {
            if (!justAte) {
                for (int i = tailLength - 1; i > 0; i--) {
                    tailX[i] = tailX[i - 1];
                    tailY[i] = tailY[i - 1];
                }
            }
        }
    }

    // Update the position of the snake
    {
        if (dir != Direction::STOP) {
            switch (dir) {
                case Direction::UP:
                    y -= speed;
                    break;
                case Direction::DOWN:
                    y += speed;
                    break;
                case Direction::LEFT:
                    x -= speed;
                    break;
                case Direction::RIGHT:
                    x += speed;
                    break;
            }
        }
    }

    // Wrap around the screen
    {
        if (x < 0) {
            x = GRID_WIDTH - 1;
        } else if (x >= GRID_WIDTH) {
            x = 0;
        }

        if (y < 0) {
            y = GRID_HEIGHT - 1;
        } else if (y >= GRID_HEIGHT) {
            y = 0;
        }
    }

    // Update the tail positions
    if (!justAte) {
        // Move each segment to the position of the preceding segment
        for (int i = tailLength - 1; i > 0; i--) {
            tailX[i] = tailX[i - 1];
            tailY[i] = tailY[i - 1];
        }
        // Move the first segment to the previous position of the head
        tailX[0] = prevX;
        tailY[0] = prevY;
    }

    // if the snake is on the same position as the consumable, eat it
    if (std::any_of(consumables.begin(), consumables.end(), [this](const std::shared_ptr<Consumable>& consumable) {
        return x == consumable->getX() && y == consumable->getY();
    })) {
        extendTail();

        // remove the consumable from the list
        consumables.remove_if([this](const std::shared_ptr<Consumable>& consumable) {
            return x == consumable->getX() && y == consumable->getY();
        });
    }

    // if the snake collides with itself, reset the game
    if (selfCollision()) {
        reset();
    }

    justAte = false;
}

void Snake::changeDirection(Direction direction) {
    dir = direction;
}

void Snake::draw(SDL_Renderer* renderer) {
    for (int i = 0; i < tailLength; i++) {
        drawRect(renderer, tailX[i] * 16, tailY[i] * 16, 16, 16, {0, 255, 0, 255});
    }

    drawRect(renderer, x * 16, y * 16, 16, 16, {0, 255, 255, 255});
}

bool Snake::selfCollision() {
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            return true;
        }
    }

    return false;
}

void Snake::reset() {
    x = GRID_WIDTH / 2;
    y = GRID_HEIGHT / 2;
    speed = 1;
    tailLength = 0;
    dir = Direction::STOP;
    for (int i = 0; i < 100; i++) {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

int Snake::getX() const {
    return x;
}

int Snake::getY() const {
    return y;
}

int Snake::getTailLength() const {
    return tailLength;
}

int Snake::getTailX(int index) {
    return tailX[index];
}

int Snake::getTailY(int index) {
    return tailY[index];
}

Direction Snake::getDirection() {
    return dir;
}
