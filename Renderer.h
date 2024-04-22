#ifndef SDL_SNAKE_RENDERER_H
#define SDL_SNAKE_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, const SDL_Color& color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = surface->w;
    textRect.h = surface->h;

    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

TTF_Font* loadFont(const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(("../fonts/" + path + ".ttf").c_str(), size);
    if (font == nullptr) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    return font;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ("../textures/" + path).c_str());
    if(texture == nullptr) {
        printf("IMG_LoadTexture: %s\n", IMG_GetError());
    }

    return texture;
}

void loadTextureSize(SDL_Texture* texture, int& width, int& height) {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

#endif //SDL_SNAKE_RENDERER_H
