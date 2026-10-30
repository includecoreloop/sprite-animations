#include "animation_system.hpp"
#include "../../engine/core/config.hpp"

namespace Engine::Systems {
    void AnimationSystem::update(Context &context, const double dt) noexcept {
        for (std::size_t i = 0; i < Core::Config::MAX_ENTITIES; ++i) {
            if (context.animated_sprites.has(i) && context.renders.has(i)) {
                auto *anim = context.animated_sprites.get(i);

                auto *clip = anim->get_current_clip();

                anim->frame_timer += static_cast<float>(dt) * anim->speed;

                while (anim->frame_timer >= clip->frame_duration) {
                    anim->frame_timer -= clip->frame_duration;
                    anim->current_frame++;

                    if (anim->current_frame >= clip->frame_count) {
                        if (clip->is_looping) {
                            anim->current_frame = 0;
                        } else {
                            anim->current_frame = clip->frame_count - 1;
                        }
                    }
                }
            }
        }
    }
}
