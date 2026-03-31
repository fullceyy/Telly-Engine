#pragma once
#include "Central.hpp"
#include "Font.hpp"
#include "Section.hpp"
#include <string>
#include <vector>
#include <iostream>

class Menu : public Section
{
    private:
        SDL_Renderer* m_rH; 

        SDL_Color m_RectBorderColor;
        SDL_Color m_RectFillColor;
        SDL_Color m_TextColor;

        struct Referrable {
            SDL_FRect rect_data;
            std::string display_text;
            SDL_Texture* texture;
            // SDL_Color fillColor;
            // SDL_Color textColor;
            // SDL_Color borderColor;
            bool hovered;

            Referrable()
            : rect_data({0, 0, 0, 0}), 
                display_text("0"), 
                texture(nullptr),
                hovered(false) 
                // fillColor({0, 0, 0, 0}), 
                // textColor({0, 0, 0, 0})
            {}
        };
        

        std::vector<Referrable*> m_Rfs;
    public:
        Menu(SDL_Renderer*);
        ~Menu();

        void create_menu();
        void render() override;
        void handle(SDL_Event& e) override;
        void update() override;
};