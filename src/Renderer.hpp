#pragma once
#include <iostream>
#include "SDL3/SDL.h"
#include "Font.hpp"

class Renderer 
{
    private:
        SDL_Renderer* m_Renderer;
    public:
        Renderer();
        ~Renderer();

        void create(SDL_Window* window);

        SDL_INLINE SDL_Renderer* get() const { return m_Renderer; }
};