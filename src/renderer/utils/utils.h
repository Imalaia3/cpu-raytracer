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
        return lower+(upper-lower)*((float)std::rand()/(float)RAND_MAX);
    }

    // eta = η
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/refract.xhtml
    // Return a refraction vector using Snell's Law
    inline glm::vec3 refract(glm::vec3 incident, glm::vec3 normal, float eta) {
        float cosTheta = glm::dot(incident, normal);
        float k = 1.0f - eta*eta * (1.0f - cosTheta*cosTheta);
        // If k < 0.0f then total internal reflection has occurred (eg light reflecting from water when looking up at the sea)
        if (k < 0.0f)
            return glm::vec3(0.0f);
        return eta * incident - (eta * cosTheta + glm::sqrt(k)) * normal;
    }

    // https://martin.ankerl.com/2012/01/25/optimized-approximative-pow-in-c-and-cpp/
    // Approximative pow(). Use with caution
    inline double fastPow(double a, double b) {
        union {
            double d;
            int x[2];
        } u = { a };
        u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
        u.x[0] = 0;
        return u.d;
    }

    // https://en.wikipedia.org/wiki/Schlick%27s_approximation
    // Returns: Reflection Coefficient (R)
    // surroundingIOR is by default 1.0 (air)
    inline float schlickApproximation(float cosTheta, float objectIOR, float surroundingIOR = 1.0f) {
        // ((surroundingIOR - objectIOR) / (surroundingIOR + objectIOR)) squared
        float R0 = ((surroundingIOR - objectIOR) / (surroundingIOR + objectIOR));
        R0 *= R0;
        float x = 1.0f-cosTheta; // x^5
        return R0 + (1.0f - R0)*(x*x*x*x*x);
    }


} // namespace Utils
