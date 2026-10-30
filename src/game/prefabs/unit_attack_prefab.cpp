#include "unit_attack_prefab.hpp"

#include "../../engine/components/animated_sprite.hpp"
#include "../../engine/core/config.hpp"

namespace Game::Prefabs {
    using Engine::ECS::Entity;

    Entity UnitAttackPrefab::create(Context &context) noexcept {
        const Entity entity = context.engine.entities.create();

        constexpr Engine::Core::Math::Vector2 pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f - 500.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f + 200.0f
        };

        context.engine.transforms.add(entity, {.position = pos});
        context.engine.renders.add(entity);

        Engine::Components::AnimatedSprite anim_sprite{};

        anim_sprite.clips[0].set_fps(16.0f);
        anim_sprite.clips[0].frame_count =
                context.texture_manager.load_sequence<Engine::Core::Config::MAX_ANIMATION_FRAMES>(
                    context.renderer,
                    "assets/textures/hooded-blade-attack/tile%03d.png",
                    0,
                    32,
                    anim_sprite.clips[0].frame_ids
                );
        anim_sprite.clip_count = 1;

        context.engine.animated_sprites.add(entity, anim_sprite);

        return entity;
    }

    void UnitAttackPrefab::destroy(const Entity entity, Context &context) noexcept {
        context.engine.transforms.remove(entity);
        context.engine.renders.remove(entity);
        context.engine.animated_sprites.remove(entity);

        context.engine.entities.destroy(entity);
    }
}
