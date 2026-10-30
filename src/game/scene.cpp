#include "scene.hpp"

#include "prefabs/unit_prefab.hpp"
#include "prefabs/unit_attack_prefab.hpp"
#include "prefabs/dude_prefab.hpp"
#include "prefabs/fire_prefab.hpp"
#include "prefabs/sword_prefab.hpp"

namespace Game {
    void Scene::init(Context &context) noexcept {
        state = SceneState::Running;

        // static character sprite
        Engine::ECS::Entity unit = Prefabs::UnitPrefab::create(context);
        // animated character sprite
        Engine::ECS::Entity unit_attack = Prefabs::UnitAttackPrefab::create(context);

        constexpr Engine::Core::Math::Vector2 dude_pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f - 400.0f
        };

        Engine::ECS::Entity dude = Prefabs::DudePrefab::create(context, dude_pos, 1.0f, false);

        constexpr Engine::Core::Math::Vector2 dude2_pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f - 400.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f - 400.0f
        };

        Engine::ECS::Entity dude2 = Prefabs::DudePrefab::create(context, dude2_pos, 2.0f, true);

        constexpr Engine::Core::Math::Vector2 fire_pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f + 400.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f - 400.0f
        };

        Engine::ECS::Entity fire = Prefabs::FirePrefab::create(context, fire_pos);

        constexpr Engine::Core::Math::Vector2 sword_pos = {
            .x = Engine::Core::Config::SCREEN_WIDTH / 2.0f + 400.0f,
            .y = Engine::Core::Config::SCREEN_HEIGHT / 2.0f + 200.0f,
        };

        Engine::ECS::Entity sword = Prefabs::SwordPrefab::create(context, sword_pos);
    }
}
