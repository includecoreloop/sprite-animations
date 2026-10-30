#pragma once

#include <SDL3/SDL_render.h>
#include <cstdint>
#include <cstdio>
#include "../../engine/core/config.hpp"

namespace Asset::SDL3 {
    struct TextureManager {
        SDL_Texture *textures[Engine::Core::Config::MAX_TEXTURES]{};
        char paths[Engine::Core::Config::MAX_TEXTURES][128]{};
        std::uint32_t texture_count{0};

        void init() noexcept;

        std::uint32_t load(SDL_Renderer *renderer, const char *file_path) noexcept;

        [[nodiscard]] SDL_Texture *get(std::uint32_t id) const noexcept;

        void unload_all() noexcept;

        template<std::size_t N>
        std::uint32_t load_sequence(SDL_Renderer *renderer, const char *base_path_format,
                                    const std::uint32_t start_index, const std::uint32_t count,
                                    std::uint32_t out_frame_ids[N]) noexcept {
            for (std::uint32_t i = 0; i < count; ++i) {
                char file_path[128];
                std::snprintf(file_path, sizeof(file_path), base_path_format, start_index + i);
                out_frame_ids[i] = load(renderer, file_path);
            }

            return count;
        }
    };
}
