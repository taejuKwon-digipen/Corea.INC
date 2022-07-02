#pragma once
#include <utility>
#include "Engine.h"
#include "glslshader.h"

namespace coconut {
    namespace math {
        struct [[nodiscard]] rect2 {
            glm::vec2 point1{ 0.0, 0.0 };
            glm::vec2 point2{ 0.0, 0.0 };

            constexpr glm::vec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
            constexpr double Left() const noexcept { return std::min(point1.x, point2.x); }     // if the rect was flipped, then bottomLeft.x > topRight.x
            constexpr double Right() const noexcept { return std::max(point1.x, point2.x); }    // if the rect was flipped, then bottomLeft.x > topRight.x
            constexpr double Top() const noexcept { return std::max(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
            constexpr double Bottom() const noexcept { return std::min(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
        };
        struct [[nodiscard]] irect2 {
            glm::ivec2 point1{ 0, 0 };
            glm::ivec2 point2{ 0, 0 };

            constexpr glm::ivec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
            constexpr int Left() const noexcept { return std::min(point1.x, point2.x); }     // if the rect was flipped, then bottomLeft.x > topRight.x
            constexpr int Right() const noexcept { return std::max(point1.x, point2.x); }    // if the rect was flipped, then bottomLeft.x > topRight.x
            constexpr int Top() const noexcept { return std::max(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
            constexpr int Bottom() const noexcept { return std::min(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
        };
    };

}