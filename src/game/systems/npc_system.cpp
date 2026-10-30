#include "npc_system.hpp"

#include "../tags.hpp"
#include "../../engine/core/config.hpp"
#include "../../engine/components/animated_sprite.hpp"

namespace Game::Systems {
    void NPCSystem::update(Context &context, const double dt) noexcept {
        static float switch_timer = 0.0f;
        switch_timer += static_cast<float>(dt);

        if (switch_timer >= 3.0f) {
            switch_timer = 0.0f;

            for (std::size_t i = 0; i < Engine::Core::Config::MAX_ENTITIES; ++i) {
                if (context.engine.tags.has(i)) {
                    const auto *tags = context.engine.tags.get(i);

                    if (tags->has(Tags::Dude)) {
                        auto *sprite = context.engine.animated_sprites.get(i);

                        const std::size_t next_clip = (sprite->current_clip_index + 1) % sprite->clip_count;
                        sprite->play(next_clip);
                    }
                }
            }
        }
    }
}
