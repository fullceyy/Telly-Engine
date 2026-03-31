#include "Central.hpp"

STATE Central::m_State = STATE::MENU;
std::function<void(STATE)> Central::on_state_change = nullptr;

Central::Central()
{
}

Central::~Central()
{
}

void Central::notify(STATE new_state)
{
    if(m_State != new_state)
    {
        m_State = new_state;
        if(on_state_change)
            on_state_change(m_State);
    }    
    else return;    
}