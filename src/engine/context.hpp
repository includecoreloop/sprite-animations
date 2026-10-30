#pragma once

#include "../engine/ecs/ecs.hpp"
#include "../engine/components/transform.hpp"
#include "../engine/components/render.hpp"
#include "../engine/components/sprite.hpp"
#include "../engine/components/animated_sprite.hpp"
#include "../engine/components/tags.hpp"

namespace Engine {
    struct Context {
        ECS::EntityManager entities{};

        ECS::ComponentStore<Components::Transform> transforms{};
        ECS::ComponentStore<Components::Render> renders{};
        ECS::ComponentStore<Components::Sprite> sprites{};
        ECS::ComponentStore<Components::AnimatedSprite> animated_sprites{};
        ECS::ComponentStore<Components::Tags> tags{};

        void clear() noexcept {
            entities = ECS::EntityManager{};
            transforms = {};
            renders = {};
            sprites = {};
            animated_sprites = {};
            tags = {};
        }
    };
}
