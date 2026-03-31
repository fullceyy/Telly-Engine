#include "Window.hpp"

Window::Window()
: m_Window(nullptr), m_Width(0), m_Height(0), m_Open(false)
{
}

Window::~Window()
{
    if(m_Window)
        SDL_DestroyWindow(m_Window);
}

void Window::create(int width, int height)
{
    if(m_Window == nullptr)
    {
        m_Window = SDL_CreateWindow("Telly", width, height, 0);
        m_Open = true;
        m_Width = width;
        m_Height = height;
    } else {
        std::cout << "m_Window is already created.\n";
    }
}

void Window::close_request()
{
    m_Open = false;
}

void Window::handle(SDL_Event& e)
{
    switch(e.type) {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            m_Open = false;
            break;
        case SDL_EVENT_WINDOW_MOUSE_ENTER:
            SDL_SetWindowTitle(m_Window, "Inside");
            break;
        case SDL_EVENT_WINDOW_MOUSE_LEAVE:
            SDL_SetWindowTitle(m_Window, "Outside");
            break;
    }
}