#pragma once

#include "../context.hpp"

namespace Game::Systems {
    struct NPCSystem {
        static void update(Context &context, double dt) noexcept;
    };
}