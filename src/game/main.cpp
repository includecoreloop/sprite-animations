#include <iostream>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

#include "context.hpp"
#include "scene.hpp"

#include "../engine/core/config.hpp"
#include "../engine/systems/animation_system.hpp"

#include "systems/npc_system.hpp"
#include "systems/SDL3/render_system.hpp"

namespace Config = Engine::Core::Config;

static void tick(Game::Context &context, const double dt) {
    Game::Systems::NPCSystem::update(context, dt);
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        Config::WINDOW_TITLE.data(),
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    Game::Context context{};
    context.renderer = renderer;
    context.texture_manager.init();

    Game::Scene scene;
    scene.init(context);

    Uint64 previous = SDL_GetTicksNS();
    double accumulator = 0.0;
    bool is_running = true;

    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
        }

        const Uint64 current = SDL_GetTicksNS();
        double frameTime = static_cast<double>(current - previous) / SDL_NS_PER_SECOND;
        previous = current;

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        accumulator += frameTime;

        while (accumulator >= Config::FIXED_DT) {
            tick(context, Config::FIXED_DT);
            accumulator -= Config::FIXED_DT;
        }

        Engine::Systems::AnimationSystem::update(context.engine, frameTime);
        Game::Systems::SDL3::RenderSystem::update(context);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
