cmake_minimum_required(VERSION 3.28)
project(SDL_Snake)

include_directories("F:/CPP-Libs/SDL2/include")
include_directories("F:/CPP-Libs/SDL2_ttf/include")
include_directories("F:/CPP-Libs/SDL2_image/include")

set(CMAKE_CXX_STANDARD 17)

add_executable(SDL_Snake main.cpp
        Snake.cpp
        Snake.h
        Consumable.cpp
        Consumable.h
        Constants.h
        Renderer.h
        Apple.h)

target_link_libraries(SDL_Snake "F:/CPP-Libs/SDL2/lib/x64/SDL2.lib")
target_link_libraries(SDL_Snake "F:/CPP-Libs/SDL2_ttf/lib/x64/SDL2_ttf.lib")
target_link_libraries(SDL_Snake "F:/CPP-Libs/SDL2_image/lib/x64/SDL2_image.lib")