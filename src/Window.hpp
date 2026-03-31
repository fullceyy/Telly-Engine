#pragma once
#include "SDL3/SDL.h"
#include <iostream>

class Window
{
    private:
        SDL_Window* m_Window;
        int m_Width;
        int m_Height;
        bool m_Open;
    public:
        Window();
        ~Window();

        void create(int width, int height);
        void close_request();
        void handle(SDL_Event& e);
        
        SDL_INLINE SDL_Window* get() const { return m_Window; }
        SDL_INLINE bool open() { return m_Open; }
};