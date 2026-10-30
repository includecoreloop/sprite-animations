#pragma once

#include "../context.hpp"

namespace Engine::Systems {
    struct AnimationSystem {
        static void update(Context &context, double dt) noexcept;
    };
}
