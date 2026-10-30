#pragma once

#include "context.hpp"

namespace Game {
    enum class SceneState : std::uint8_t {
        Loading,
        Running,
    };

    struct Scene {
        SceneState state{SceneState::Loading};

        void init(Context &context) noexcept;
    };
}
