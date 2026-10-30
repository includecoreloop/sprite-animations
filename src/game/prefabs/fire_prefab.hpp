#pragma once

#include "../../engine/ecs/ecs.hpp"
#include "../context.hpp"

namespace Game::Prefabs {
    struct FirePrefab {
        [[nodiscard]] static Engine::ECS::Entity create(Context &context, Engine::Core::Math::Vector2 pos) noexcept;

        static void destroy(Engine::ECS::Entity entity, Context &context) noexcept;
    };
}
