#include "Start.hpp"
#include "Menu.hpp"
#include "Central.hpp"
#include "Window.hpp"
#include "Renderer.hpp"


int main(void)
{
    Window win;
    win.create(800, 600);

    Renderer rend;
    rend.create(win.get());

    std::vector<Section*> sections = { new Menu(rend.get()), new Start(rend.get()) };
 
    auto state_to_idx = [](STATE s) -> int
    {
        switch(s)
        {
            case STATE::MENU:
                return 0;
                break;
            case STATE::START:
                return 1;
                break;
            default:
                return 0;
        }
    };

    Central::on_state_change = [&](STATE s)
    {
        if(s == STATE::EXIT)
            win.close_request();
    };

    std::string name = SDL_GetRendererName(rend.get());
    std::cout << name;
    SDL_Event e;

    while(win.open())
    {
        int idx = state_to_idx(Central::m_State);
        
        while(SDL_PollEvent(&e))
        {
            if(e.type >= SDL_EVENT_WINDOW_FIRST && e.type <= SDL_EVENT_WINDOW_LAST)
            {
                win.handle(e);
            }    
            if(e.type == SDL_EVENT_MOUSE_MOTION || e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                sections[idx]->handle(e);
            }
        }

        SDL_SetRenderDrawColor(rend.get(), 26, 26, 26, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(rend.get());
        
        sections[idx]->render();
        sections[idx]->update();
        SDL_RenderPresent(rend.get());
    }    

    return 0;
}