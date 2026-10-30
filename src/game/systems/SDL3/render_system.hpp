#pragma once

#include "../../context.hpp"

namespace Game::Systems::SDL3 {
    struct RenderSystem {
        static void draw_sprite(Context &context, std::size_t i);

        static void update(Context &context) noexcept;
    };
}
