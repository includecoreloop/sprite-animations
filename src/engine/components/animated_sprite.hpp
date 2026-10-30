#pragma once

#include <cstdint>
#include "../core/config.hpp"

namespace Engine::Components {
    struct AnimationClip {
        std::uint32_t frame_ids[Core::Config::MAX_ANIMATION_FRAMES]{};
        std::uint32_t frame_count{0};

        float frame_duration{1.0f / static_cast<float>(Core::Config::DEFAULT_ANIMATION_FPS)};
        bool is_looping{true};

        void set_fps(const float fps) noexcept {
            frame_duration = 1.0f / fps;
        }
    };

    struct AnimatedSprite {
        AnimationClip clips[Core::Config::MAX_ANIMATION_CLIPS_PER_ANIMATED_SPRITE]{};
        std::size_t clip_count{0};

        std::size_t current_clip_index{0};
        std::uint32_t current_frame{0};

        float frame_timer{0.0f};
        float speed{1.0f};

        void play(const std::size_t index) noexcept {
            if (current_clip_index != index) {
                current_clip_index = index;
                current_frame = 0;
                frame_timer = 0.0f;
            }
        }

        [[nodiscard]] const AnimationClip *get_current_clip() const noexcept {
            return &clips[current_clip_index];
        }
    };
}
