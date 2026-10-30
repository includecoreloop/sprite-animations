#pragma once

#include <cstdint>
#include <bitset>
#include <array>
#include <utility>

#include "../core/config.hpp"

namespace Engine::ECS {
    using Entity = std::uint32_t;
    constexpr Entity NULL_ENTITY = Core::Config::MAX_ENTITIES;

    struct EntityManager {
        std::array<Entity, Core::Config::MAX_ENTITIES> free_list{};
        std::size_t free_count = 0;

        constexpr EntityManager() noexcept {
            for (Entity i = 0; i < Core::Config::MAX_ENTITIES; ++i) {
                free_list[i] = static_cast<Entity>(Core::Config::MAX_ENTITIES - 1 - i);
            }

            free_count = Core::Config::MAX_ENTITIES;
        }

        [[nodiscard]] Entity create() noexcept {
            if (free_count == 0)
                return NULL_ENTITY;

            return free_list[--free_count];
        }

        void destroy(const Entity e) noexcept {
            if (e >= Core::Config::MAX_ENTITIES)
                return;

            free_list[free_count++] = e;
        }
    };

    template<typename T>
    struct ComponentStore {
        std::array<T, Core::Config::MAX_ENTITIES> data{};
        std::bitset<Core::Config::MAX_ENTITIES> mask;

        T &add(Entity e, T component = {}) noexcept {
            mask.set(e);
            data[e] = std::move(component);

            return data[e];
        }

        void remove(Entity e) noexcept {
            mask.reset(e);
            data[e] = T{};
        }

        [[nodiscard]] bool has(const Entity e) const noexcept {
            return mask.test(e);
        }

        [[nodiscard]] T *get(Entity e) noexcept {
            return  &data[e];
        }
    };
}
