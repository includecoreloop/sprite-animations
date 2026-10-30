#pragma once

#include <cstdint>

namespace Engine::Components {
    struct Tags {
        std::uint32_t mask{0};

        [[nodiscard]] bool has(const std::uint32_t flag) const noexcept {
            return (mask & flag) != 0;
        }

        void add(const std::uint32_t flag) noexcept {
            mask |= flag;
        }

        void remove(const std::uint32_t flag) noexcept {
            mask &= ~flag;
        }
    };
}
