#ifndef SDL_SNAKE_CONSUMABLE_H
#define SDL_SNAKE_CONSUMABLE_H

#include <list>
#include <random>
#include <functional>
#include <memory>
#include <SDL_render.h>
#include "Constants.h"

class Consumable {
private:
    int x{}, y{};
public:
    Consumable();
    virtual void spawn(std::list<std::shared_ptr<Consumable>>& consumables, const std::function<bool(int, int)>& isSnake);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    virtual void draw(SDL_Renderer* renderer) const;
    virtual void update(std::list<std::shared_ptr<Consumable>>& consumables);
    virtual void addToList(std::list<std::shared_ptr<Consumable>>& consumables);

    static int getRandomNumber(int min, int max) {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }
};

#endif //SDL_SNAKE_CONSUMABLE_H
