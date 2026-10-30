#include "dude_prefab.hpp"

#include "../tags.hpp"
#include "../../engine/components/animated_sprite.hpp"
#include "../../engine/core/config.hpp"

namespace Game::Prefabs {
    using Engine::ECS::Entity;

    Entity DudePrefab::create(Context &context, const Engine::Core::Math::Vector2 pos, const float anim_speed,
                              const bool flip_horizontal) noexcept {
        const Entity entity = context.engine.entities.create();

        const Engine::Components::Transform transform = {
            .position = pos, .scale = {.x = 1.5f, .y = 1.5f}, .flip_horizontal = flip_horizontal
        };

        context.engine.transforms.add(entity, transform);
        context.engine.renders.add(entity);

        Engine::Components::AnimatedSprite anim_sprite{};

        anim_sprite.clips[0].set_fps(16.0f);
        anim_sprite.clips[0].frame_count =
                context.texture_manager.load_sequence<Engine::Core::Config::MAX_ANIMATION_FRAMES>(
                    context.renderer,
                    "assets/textures/dude/idle/tile%03d.png",
                    0,
                    23,
                    anim_sprite.clips[0].frame_ids
                );

        anim_sprite.clips[1].set_fps(16.0f);
        anim_sprite.clips[1].frame_count =
                context.texture_manager.load_sequence<Engine::Core::Config::MAX_ANIMATION_FRAMES>(
                    context.renderer,
                    "assets/textures/dude/walk/tile%03d.png",
                    0,
                    21,
                    anim_sprite.clips[1].frame_ids
                );

        anim_sprite.clips[2].set_fps(16.0f);
        anim_sprite.clips[2].frame_count =
                context.texture_manager.load_sequence<Engine::Core::Config::MAX_ANIMATION_FRAMES>(
                    context.renderer,
                    "assets/textures/dude/aim/tile%03d.png",
                    0,
                    25,
                    anim_sprite.clips[2].frame_ids
                );

        anim_sprite.clips[2].is_looping = false;

        anim_sprite.speed = anim_speed;

        anim_sprite.clip_count = 3;

        context.engine.animated_sprites.add(entity, anim_sprite);

        context.engine.tags.add(entity, {.mask = Game::Tags::Dude});

        return entity;
    }

    void DudePrefab::destroy(const Entity entity, Context &context) noexcept {
        context.engine.transforms.remove(entity);
        context.engine.renders.remove(entity);
        context.engine.animated_sprites.remove(entity);
        context.engine.tags.remove(entity);

        context.engine.entities.destroy(entity);
    }
}
