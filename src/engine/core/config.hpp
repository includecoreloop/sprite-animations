#pragma once

#include <string_view>

namespace Engine::Core::Config {
    constexpr int32_t SCREEN_WIDTH = 1920;
    constexpr int32_t SCREEN_HEIGHT = 1200;
    constexpr std::string_view WINDOW_TITLE = "Animate Sprites";

    constexpr double TARGET_FPS = 120.0;
    constexpr double TARGET_TPS = 120.0;
    constexpr double FIXED_DT = 1.0 / TARGET_TPS;

    constexpr std::size_t MAX_ENTITIES = 64;
    constexpr std::size_t MAX_TEXTURES = 512;
    constexpr std::size_t MAX_ANIMATION_FRAMES = 32;
    constexpr std::size_t MAX_ANIMATION_CLIPS_PER_ANIMATED_SPRITE = 8;

    constexpr double DEFAULT_ANIMATION_FPS = 12.0;
}
