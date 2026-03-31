#include "Start.hpp"

Start::Start(SDL_Renderer* r)
: m_rH(r), m_BoardState(BOARD_STATE::IDLE)
{
    m_Rfs.resize(16);
    for(auto& rf : m_Rfs)
        rf = new Referrable();

    create_start();
}

Start::~Start()
{
    m_rH = nullptr;
    for(auto& rf : m_Rfs)
    {
        SDL_DestroyTexture(rf->rect_texture);
        SDL_DestroyTexture(rf->reveal_texture);
        delete rf;
    }    
}

void Start::create_start()
{
    std::vector<int> indices;
    for(int q = 1; q <= (int)m_Rfs.size() / 2; q++)
    {
        indices.push_back(q);
        indices.push_back(q);
    }

    std::mt19937 rng(std::random_device{}());
    std::shuffle(indices.begin(), indices.end(), rng);

    std::stringstream ss;
    for(size_t q = 0; q < m_Rfs.size(); q++)
    {
        ss << "include/Image/" << indices[q] << ".png";
        m_Rfs[q]->rect_texture = IMG_LoadTexture(m_rH, "include/Image/qmark.png");
        m_Rfs[q]->reveal_texture = IMG_LoadTexture(m_rH, ss.str().c_str());
        m_Rfs[q]->pair_idx = indices[q];
        std::cout << ss.str() << std::endl;
        ss.str(std::string());
    }

    int w, h;
    SDL_GetCurrentRenderOutputSize(m_rH, &w, &h);

    const int element_width  = 80;
    const int element_height = 80;
    const int padding        = 15;
    const int grid_size      = DEFAULT_GRID_SIZE;

    int total_width  = grid_size * element_width + (grid_size - 1) * padding;
    int total_height = grid_size * element_height + (grid_size - 1) * padding;

    int start_x = (w - total_width) / 2;
    int start_y = (h - total_height) / 2;

    for (size_t i = 0; i < m_Rfs.size(); ++i)
    {
        int row = i / grid_size;
        int col = i % grid_size;

        m_Rfs[i]->rect_data.w = element_width;
        m_Rfs[i]->rect_data.h = element_height;
        m_Rfs[i]->rect_data.x = start_x + col * (element_width + padding);
        m_Rfs[i]->rect_data.y = start_y + row * (element_height + padding);
    }
}

void Start::render()
{
    for(auto& rf : m_Rfs)
    {
        if(rf->clicked || rf->matched) // BUG 3: matched cards were re-hidden because only `clicked` was checked; matched cards should always show their reveal texture
            SDL_RenderTexture(m_rH, rf->reveal_texture, nullptr, &rf->rect_data);
        else
            SDL_RenderTexture(m_rH, rf->rect_texture, nullptr, &rf->rect_data);
    }
}

void Start::handle(SDL_Event& e)
{
    if(inputLocked) return;

    SDL_FPoint p;
    p = { .x = e.motion.x, .y = e.motion.y };

    for(size_t q = 0; q < m_Rfs.size(); q++)
    {
        m_Rfs[q]->hovered = SDL_PointInRectFloat(&p, &m_Rfs[q]->rect_data);

        if(!m_Rfs[q]->clicked && !m_Rfs[q]->matched) // BUG 4: hover alpha was applied to matched cards, visually disrupting them
            SDL_SetTextureAlphaMod(m_Rfs[q]->rect_texture, m_Rfs[q]->hovered ? 65 : 255);
        
        if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && m_Rfs[q]->hovered && !m_Rfs[q]->clicked && !m_Rfs[q]->matched) // BUG 5: matched cards could still be clicked and re-entered into game logic
        {
            m_Rfs[q]->clicked = true;

            switch(m_BoardState)
            {    
                case BOARD_STATE::IDLE:
                    fPull = q;
                    m_BoardState = BOARD_STATE::SINGLE;
                    break;

                case BOARD_STATE::SINGLE:
                    sPull = q;
                    m_BoardState = BOARD_STATE::DOUBLE;

                    if(m_Rfs[fPull]->pair_idx == m_Rfs[sPull]->pair_idx)
                    {
                        m_Rfs[fPull]->matched = true;
                        m_Rfs[sPull]->matched = true;

                        fPull = -1;
                        sPull = -1;

                        m_BoardState = BOARD_STATE::IDLE;
                    } else 
                    {
                        inputLocked = true;
                        bTimer.start();
                    }
                    break;

                case BOARD_STATE::DOUBLE:
                    break;
            }
        }
    }
}

void Start::update()
{
    if(m_BoardState == BOARD_STATE::DOUBLE && inputLocked)
    {
        if(bTimer.getNS() >= 1'000'000'000ULL)
        {
            bTimer.stop();

            m_Rfs[fPull]->clicked = false;
            m_Rfs[sPull]->clicked = false;

            SDL_SetTextureAlphaMod(m_Rfs[fPull]->rect_texture, 255);
            SDL_SetTextureAlphaMod(m_Rfs[sPull]->rect_texture, 255);

            fPull = -1;
            sPull = -1;

            inputLocked = false;
            m_BoardState = BOARD_STATE::IDLE;
        }
    }
}