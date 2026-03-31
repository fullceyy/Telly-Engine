#include "Menu.hpp"

Menu::Menu(SDL_Renderer* r)
: m_rH(r), 
    m_RectBorderColor({ .r = 83, .g = 58, .b = 183, .a = SDL_ALPHA_OPAQUE }), 
    m_RectFillColor({ .r = 22, .g = 33, .b = 62, .a = SDL_ALPHA_OPAQUE }),
    m_TextColor({ .r = 175, .g = 169, .b = 236, .a = SDL_ALPHA_OPAQUE })
{
    m_Rfs.resize(2);
    for(auto& rf : m_Rfs)
    {
        rf = new Referrable();
        // rf->fillColor = { .r = 22, .g = 33, .b = 62, .a = SDL_ALPHA_OPAQUE };
        // rf->textColor = { .r = 175, .g = 169, .b = 236, .a = SDL_ALPHA_OPAQUE };
        // rf->borderColor = { .r = 83, .g = 58, .b = 183, .a = SDL_ALPHA_OPAQUE };
    }
    m_Rfs[0]->display_text = "PLAY";
    m_Rfs[1]->display_text = "EXIT";
    create_menu();
}

Menu::~Menu()
{
    m_rH = nullptr;
    for(auto& rf : m_Rfs)
    {
        SDL_DestroyTexture(rf->texture);
        delete rf;
    }
}

void Menu::create_menu()
{
    for(auto& rf : m_Rfs)
    {
        SDL_Surface* surface = TTF_RenderText_Blended(font, rf->display_text.c_str(), 0, m_TextColor);
        rf->texture = SDL_CreateTextureFromSurface(m_rH, surface);
        SDL_DestroySurface(surface);
    }

    int w, h;
    SDL_GetCurrentRenderOutputSize(m_rH, &w, &h);

    const int element_width  = 105;
    const int element_height = 65;
    const int padding        = 35;

    // total height of all elements + padding between them
    int total_height = m_Rfs.size() * element_height + (m_Rfs.size() - 1) * padding;

    // starting Y for the first element (top-left corner)
    int start_y = (h - total_height) / 2;

    // X is same for all elements, center horizontally
    int center_x = (w - element_width) / 2;

    for (size_t i = 0; i < m_Rfs.size(); ++i) 
    {
        m_Rfs[i]->rect_data.w = element_width;
        m_Rfs[i]->rect_data.h = element_height;
        m_Rfs[i]->rect_data.x = center_x;
        m_Rfs[i]->rect_data.y = start_y + i * (element_height + padding);
    }
}

void Menu::render()
{
    for(auto& rf : m_Rfs)
    {
        if(rf->hovered)
        {
            SDL_SetRenderDrawColor(m_rH, 40, 55, 100, SDL_ALPHA_OPAQUE);
        } else {
            SDL_SetRenderDrawColor(m_rH, m_RectFillColor.r, m_RectFillColor.g, m_RectFillColor.b, SDL_ALPHA_OPAQUE);
        }

        SDL_RenderFillRect(m_rH, &(rf)->rect_data);

        SDL_SetRenderDrawColor(m_rH, m_RectBorderColor.r, m_RectBorderColor.g, m_RectBorderColor.b, SDL_ALPHA_OPAQUE);
        SDL_RenderRect(m_rH, &(rf)->rect_data);
        // SDL_Surface* surface = TTF_RenderText_Blended(font, rf->display_text.c_str(), 0, {.r = 175, .g = 169, .b = 236, .a = SDL_ALPHA_OPAQUE});
        // SDL_Texture* texture = SDL_CreateTextureFromSurface(m_rH, surface);
        // SDL_DestroySurface(surface);
        float tx_height, tx_width;
        SDL_GetTextureSize(rf->texture, &tx_width, &tx_height);
        
        SDL_FRect text_rect = {
            rf->rect_data.x + (rf->rect_data.w - tx_width)  / 2.0f,
            rf->rect_data.y + (rf->rect_data.h - tx_height) / 2.0f,
            tx_width,
            tx_height
        };
        SDL_RenderTexture(m_rH, rf->texture, nullptr, &text_rect);
        // SDL_DestroyTexture(texture);
    }
}


// handle mouse movement / hover and press.
void Menu::handle(SDL_Event& e)
{
    SDL_FPoint p = { .x = e.motion.x, .y = e.motion.y };
    for(auto& rf : m_Rfs)
    {
        if(SDL_PointInRectFloat(&p, &rf->rect_data))
        {
            rf->hovered = true;
        } else {
            rf->hovered = false;
        }
        if(rf->hovered && e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            std::cout << "Click.\n";
            if(rf->display_text == "PLAY")
                Central::notify(STATE::START);
            if(rf->display_text == "EXIT")
                Central::notify(STATE::EXIT);
        }
    }
}

void Menu::update()
{
}