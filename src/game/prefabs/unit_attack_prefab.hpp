#pragma once

#include "../../engine/ecs/ecs.hpp"
#include "../context.hpp"

namespace Game::Prefabs {
    struct UnitAttackPrefab {
        [[nodiscard]] static Engine::ECS::Entity create(Context &context) noexcept;

        static void destroy(Engine::ECS::Entity entity, Context &context) noexcept;
    };
}
