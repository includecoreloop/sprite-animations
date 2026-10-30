#include "texture_manager.hpp"

#include <SDL3_image/SDL_image.h>
#include <cstring>

namespace Asset::SDL3 {
    void TextureManager::init() noexcept {
        texture_count = 0;

        for (std::size_t i = 0; i < Engine::Core::Config::MAX_TEXTURES; ++i) {
            textures[i] = nullptr;
            paths[i][0] = '\0';
        }
    }

    std::uint32_t TextureManager::load(SDL_Renderer *renderer, const char *file_path) noexcept {
        for (std::uint32_t i = 0; i < texture_count; ++i) {
            if (std::strcmp(paths[i], file_path) == 0) {
                return i;
            }
        }

        const std::uint32_t id = texture_count;
        textures[id] = IMG_LoadTexture(renderer, file_path);

        std::strncpy(paths[id], file_path, sizeof(paths[id]) - 1);
        paths[id][sizeof(paths[id]) - 1] = '\0';

        texture_count++;

        return id;
    }

    SDL_Texture *TextureManager::get(const std::uint32_t id) const noexcept {
        if (id >= texture_count) {
            return nullptr;
        }

        return textures[id];
    }

    void TextureManager::unload_all() noexcept {
        for (std::uint32_t i = 0; i < texture_count; ++i) {
            if (textures[i]) {
                SDL_DestroyTexture(textures[i]);
                textures[i] = nullptr;
            }
        }

        texture_count = 0;
    }
}
