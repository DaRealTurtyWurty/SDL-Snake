#ifndef SDL_SNAKE_SNAKE_H
#define SDL_SNAKE_SNAKE_H

#include <list>
#include <memory>
#include <SDL_render.h>
#include "Consumable.h"
#include "Constants.h"

enum class Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    int x{}, y{};
    int speed{};
    int tailLength{};
    int tailX[100]{}, tailY[100]{};
    Direction dir = Direction::STOP;
    bool justAte = false;
public:
    Snake();
    void update(std::list<std::shared_ptr<Consumable>>& consumables);
    void changeDirection(Direction direction);
    void extendTail();
    void draw(SDL_Renderer* pRenderer);
    bool selfCollision();
    void reset();
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getTailLength() const;
    int getTailX(int index);
    int getTailY(int index);
    Direction getDirection();
    bool isSnake(int pX, int pY);
};

#endif