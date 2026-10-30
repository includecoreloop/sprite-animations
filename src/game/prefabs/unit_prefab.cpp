#include "unit_prefab.hpp"

#include "../../engine/components/sprite.hpp"
#include "../../engine/core/config.hpp"

namespace Game::Prefabs {
    using Engine::ECS::Entity;

    Entity UnitPrefab::create(Context &context) noexcept {
        const Entity entity = context.engine.entities.create();

        constexpr Engine::Core::Math::Vector2 pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f + 200.0f,
        };

        context.engine.transforms.add(entity, {.position = pos});
        context.engine.renders.add(entity);

        const std::uint32_t sprite_id =
                context.texture_manager.load(context.renderer, "assets/textures/hooded-blade-attack/tile000.png");

        const Engine::Components::Sprite sprite = {
            .sprite_id = sprite_id,
        };

        context.engine.sprites.add(entity, sprite);

        return entity;
    }

    void UnitPrefab::destroy(const Entity entity, Context &context) noexcept {
        context.engine.transforms.remove(entity);
        context.engine.renders.remove(entity);
        context.engine.sprites.remove(entity);

        context.engine.entities.destroy(entity);
    }
}
