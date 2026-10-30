#pragma once

#include "../asset/SDL3/texture_manager.hpp"
#include "../engine/context.hpp"

namespace Game {
    struct Context {
        Engine::Context engine;

        SDL_Renderer *renderer{nullptr};
        Asset::SDL3::TextureManager texture_manager{};

        void clear() noexcept {
            engine.clear();
        }
    };
}
