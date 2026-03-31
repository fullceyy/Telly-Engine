#include "Renderer.hpp"

Renderer::Renderer()
: m_Renderer(nullptr) 
{
    if(!TTF_Init())
    {
        std::cout << "TTF_Init failed in Renderer::Renderer()!\n"; 
        return;
    }

    if(font = TTF_OpenFont("include/font/Roboto.ttf", FONT_SIZE); !font)
    {
        std::cout << "Failed to open font in Renderer::Renderer()!\n";
        return;
    }
}

Renderer::~Renderer()
{
    if(m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
}

void Renderer::create(SDL_Window* window)
{
    if(m_Renderer == nullptr)
    {
        m_Renderer = SDL_CreateRenderer(window, NULL);
    }
}