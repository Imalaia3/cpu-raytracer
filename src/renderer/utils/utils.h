#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>

namespace Utils {
    inline glm::vec3 pointInHemisphere(const glm::vec3& normal) {
        glm::vec3 point = glm::sphericalRand(1.0f);
        if (glm::dot(normal, point) < 0.0f)
            return -point;
        return point;
    }

    inline glm::vec3 colorFromNormal(const glm::vec3 normal) {
        return normal * 0.5f + 0.5f;
    }
    inline glm::vec3 colorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
        return glm::vec3(r/255.0f,g/255.0f,b/255.0f);
    }
    inline glm::vec3 colorFromHex(uint32_t hexColor) {
        uint8_t b = (hexColor & 0x0000FF);
        uint8_t g = (hexColor & 0x00FF00) >> 8;
        uint8_t r = (hexColor & 0xFF0000) >> 16;
        return colorFromRGB(r, g, b);
    }
} // namespace Utils
