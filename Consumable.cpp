#include <algorithm>
#include "Consumable.h"

Consumable::Consumable() {
    x = 0;
    y = 0;
}

void Consumable::spawn(std::list<std::shared_ptr<Consumable>>& consumables, const std::function<bool(int, int)>& isSnake) {
    x = getRandomNumber(0, GRID_WIDTH - 1);
    y = getRandomNumber(0, GRID_HEIGHT - 1);

    while (std::any_of(consumables.begin(), consumables.end(), [this](const std::shared_ptr<Consumable>& consumable) {
        return consumable->getX() == x && consumable->getY() == y;
    }) || isSnake(x, y)) {
        x = getRandomNumber(0, GRID_WIDTH - 1);
        y = getRandomNumber(0, GRID_HEIGHT - 1);
    }

    addToList(consumables);
}

void Consumable::addToList(std::list<std::shared_ptr<Consumable>>& consumables) {
    consumables.push_back(std::make_shared<Consumable>(std::move(*this)));
}

int Consumable::getX() const {
    return x;
}

int Consumable::getY() const {
    return y;
}

void Consumable::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = x * 16;
    rect.y = y * 16;
    rect.w = 16;
    rect.h = 16;
    SDL_RenderFillRect(renderer, &rect);
}

void Consumable::update(std::list<std::shared_ptr<Consumable>>& consumables) {

}

inline bool operator==(const Consumable& lhs, const Consumable& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}