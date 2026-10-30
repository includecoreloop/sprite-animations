#pragma once

#include "../../engine/ecs/ecs.hpp"
#include "../context.hpp"

namespace Game::Prefabs {
    struct DudePrefab {
        [[nodiscard]] static Engine::ECS::Entity create(Context &context, Engine::Core::Math::Vector2 pos,
                                                        float anim_speed, bool flip_horizontal) noexcept;

        static void destroy(Engine::ECS::Entity entity, Context &context) noexcept;
    };
}
