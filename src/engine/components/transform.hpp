#pragma once

#include "../core/math.hpp"

namespace Engine::Components {
    struct Transform {
        Core::Math::Vector2 position{.x = 0.0f, .y = 0.0f};
        Core::Math::Vector2 scale{.x = 1.0f, .y = 1.0f};
        Core::Math::Vector2 pivot{.x = 0.5f, .y = 0.5f};
        float rotation{0.0f};

        bool flip_horizontal{false};
        bool flip_vertical{false};
    };
}
