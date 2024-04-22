#ifndef SDL_SNAKE_APPLE_H
#define SDL_SNAKE_APPLE_H

#include "Consumable.h"
#include "Renderer.h"

class Apple : public Consumable {
private:
    SDL_Texture* texture;
    int textureWidth{}, textureHeight{};
public:
    explicit Apple(SDL_Renderer* renderer) {
        this->texture = loadTexture(renderer, "apple.png");
        loadTextureSize(texture, textureWidth, textureHeight);
    }

    ~Apple() {
        SDL_DestroyTexture(texture);
    }

    void draw(SDL_Renderer* renderer) const override {
        drawTexture(renderer, texture, getX() * 16, getY() * 16, 16, 16);
    }

    void addToList(std::list<std::shared_ptr<Consumable>>& consumables) override {
        consumables.push_back(std::make_shared<Apple>(std::move(*this)));
    }
};

#endif //SDL_SNAKE_APPLE_H
