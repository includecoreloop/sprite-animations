#include "sword_prefab.hpp"

#include "../../engine/components/animated_sprite.hpp"
#include "../../engine/core/config.hpp"

namespace Game::Prefabs {
    using Engine::ECS::Entity;

    Entity SwordPrefab::create(Context &context, const Engine::Core::Math::Vector2 pos) noexcept {
        const Entity entity = context.engine.entities.create();

        context.engine.transforms.add(entity, {.position = pos, .scale = {.x = 1.5f, .y = 1.5f}});
        context.engine.renders.add(entity);

        Engine::Components::AnimatedSprite anim_sprite{};

        anim_sprite.clips[0].set_fps(16.0f);
        anim_sprite.clips[0].frame_count =
                context.texture_manager.load_sequence<Engine::Core::Config::MAX_ANIMATION_FRAMES>(
                    context.renderer,
                    "assets/textures/sword/tile%03d.png",
                    0,
                    23,
                    anim_sprite.clips[0].frame_ids
                );

        anim_sprite.clip_count = 1;

        context.engine.animated_sprites.add(entity, anim_sprite);

        return entity;
    }

    void SwordPrefab::destroy(const Entity entity, Context &context) noexcept {
        context.engine.transforms.remove(entity);
        context.engine.renders.remove(entity);
        context.engine.animated_sprites.remove(entity);

        context.engine.entities.destroy(entity);
    }
}
