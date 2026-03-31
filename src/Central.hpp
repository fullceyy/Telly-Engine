#pragma once
#include "SDL3/SDL.h"
#include "Section.hpp"
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

enum STATE : int
{
    MENU = 0,
    START = 1,
    EXIT = 2,
};

class Central
{
    public:
        static STATE m_State;
        static std::function<void(STATE)> on_state_change;

        Central();
        ~Central();

        static void notify(STATE new_state);
        // static void request_state(int new_state);
        // static void register_state();
};
