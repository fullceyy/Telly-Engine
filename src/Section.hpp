#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

class Section
{
    public:
        virtual ~Section() = default;
        virtual void render() = 0;
        virtual void handle(SDL_Event&) = 0;
        virtual void update() = 0;
};