#pragma once
#include "Timer.hpp"
#include "Section.hpp"
#include <chrono>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>

#define DEFAULT_GRID_SIZE 4

enum class BOARD_STATE
{
    IDLE,
    SINGLE,
    DOUBLE,
    MISMATCH
};

class Start : public Section
{
    private:
        struct Referrable {
            SDL_FRect rect_data;
            SDL_Texture* rect_texture;
            SDL_Texture* reveal_texture;

            float tx_height;
            float tx_width;
            bool hovered;
            bool clicked;
            bool matched;
            int pair_idx;

            Referrable()
            : rect_data({0, 0, 0, 0}),
                rect_texture(nullptr), reveal_texture(nullptr),
                tx_height(0), tx_width(0),
                hovered(false), clicked(false), matched(false),
                pair_idx(0)
            {}
        };
        
        std::vector<Referrable*> m_Rfs;
        SDL_Renderer* m_rH;
        BOARD_STATE m_BoardState;
    public:
        Start(SDL_Renderer*);
        ~Start();

        void create_start();

        void render() override;
        void handle(SDL_Event& e) override;
        void update() override;

        Timer bTimer;
        bool inputLocked = false;
        int fPull = -1;
        int sPull = -1;
};