#include "render_system.hpp"
#include <SDL3/SDL_render.h>

namespace Game::Systems::SDL3 {
    static SDL_FlipMode resolve_flip(const Engine::Components::Transform *transform) noexcept {
        SDL_FlipMode sdl_flip = SDL_FLIP_NONE;

        if (transform->flip_horizontal && transform->flip_vertical) {
            sdl_flip = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
        } else if (transform->flip_horizontal) {
            sdl_flip = SDL_FLIP_HORIZONTAL;
        } else if (transform->flip_vertical) {
            sdl_flip = SDL_FLIP_VERTICAL;
        }

        return sdl_flip;
    }

    void RenderSystem::draw_sprite(Context &context, const std::size_t i) {
        const auto *transform = context.engine.transforms.get(i);

        SDL_Texture *texture = nullptr;

        if (context.engine.animated_sprites.has(i)) {
            const auto *anim = context.engine.animated_sprites.get(i);
            const std::uint32_t current_texture_id = anim->get_current_clip()->frame_ids[anim->current_frame];
            texture = context.texture_manager.get(current_texture_id);
        } else if (context.engine.sprites.has(i)) {
            const auto *sprite = context.engine.sprites.get(i);
            texture = context.texture_manager.get(sprite->sprite_id);
        }

        if (!texture) {
            return;
        }

        float native_w = 0.0f;
        float native_h = 0.0f;
        SDL_GetTextureSize(texture, &native_w, &native_h);

        const float scaled_w = native_w * transform->scale.x;
        const float scaled_h = native_h * transform->scale.y;

        const SDL_FRect destination_rect = {
            .x = transform->position.x - (scaled_w * transform->pivot.x),
            .y = transform->position.y - (scaled_h * transform->pivot.y),
            .w = scaled_w,
            .h = scaled_h
        };

        const SDL_FPoint center = {
            .x = scaled_w * transform->pivot.x,
            .y = scaled_h * transform->pivot.y
        };

        const SDL_FlipMode sdl_flip = resolve_flip(transform);

        SDL_RenderTextureRotated(
            context.renderer,
            texture,
            nullptr,
            &destination_rect,
            transform->rotation,
            &center,
            sdl_flip
        );
    }

    void RenderSystem::update(Context &context) noexcept {
        SDL_SetRenderDrawColor(context.renderer, 30, 30, 40, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(context.renderer);

        for (std::size_t i = 0; i < Engine::Core::Config::MAX_ENTITIES; ++i) {
            if (context.engine.renders.has(i) && context.engine.transforms.has(i) &&
                (context.engine.sprites.has(i) || context.engine.animated_sprites.has(i))) {
                draw_sprite(context, i);
            }
        }

        SDL_RenderPresent(context.renderer);
    }
}
