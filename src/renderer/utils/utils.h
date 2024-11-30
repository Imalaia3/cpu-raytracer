#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>

namespace Utils {
    inline glm::vec3 pointInHemisphere(const glm::vec3& normal) {
        glm::vec3 point = glm::sphericalRand(1.0f);
        return (glm::dot(normal, point) < 0.0f) ? -point : point;
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
    // generate a random float between lower and upper (inclusive).
    inline float randFloat(float lower, float upper) {
        return lower+(upper-lower)*(std::rand()/(float)RAND_MAX);
    }

} // namespace Utils
