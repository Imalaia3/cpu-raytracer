#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>
#include <random>

namespace Utils {
    inline glm::dvec3 pointInHemisphere(const glm::dvec3& normal) {
        glm::dvec3 point = glm::sphericalRand(1.0);
        return (glm::dot(normal, point) < 0.0) ? -point : point;
    }

    inline glm::dvec3 colorFromNormal(const glm::dvec3 normal) {
        return normal * 0.5 + 0.5;
    }
    inline glm::dvec3 colorFromRGB(uint8_t r, uint8_t g, uint8_t b) {
        return glm::dvec3(r/255.0,g/255.0,b/255.0);
    }
    inline glm::dvec3 colorFromHex(uint32_t hexColor) {
        uint8_t b = (hexColor & 0x0000FF);
        uint8_t g = (hexColor & 0x00FF00) >> 8;
        uint8_t r = (hexColor & 0xFF0000) >> 16;
        return colorFromRGB(r, g, b);
    }
    // https://entropymine.com/imageworsener/srgbformula/
    inline double linearToSRGB(double linear) {
        linear = glm::clamp(linear, 0.0, 1.0);
        return (linear <= 0.0031308) ? linear * 12.92 : 1.055*glm::pow(linear, 1.0/2.4) - 0.055;
    }
    inline glm::dvec3 linearToSRGB(glm::dvec3 linear) {
        return glm::dvec3 (
            linearToSRGB(linear.x),
            linearToSRGB(linear.y),
            linearToSRGB(linear.z)
        );
    }
    inline double SRGBToLinear(double srgb) {
        srgb = glm::clamp(srgb, 0.0, 1.0);
        return (srgb <= 0.04045) ? srgb / 12.92 : glm::pow((srgb+0.055)/1.055, 2.4);
    }
    inline glm::dvec3 SRGBToLinear(glm::dvec3 srgb) {
        return glm::dvec3 (
            SRGBToLinear(srgb.x),
            SRGBToLinear(srgb.y),
            SRGBToLinear(srgb.z)
        );
    }
    // https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
    inline glm::dvec3 toneMappingACES(glm::dvec3 in) {
        constexpr double a = 2.51;
        constexpr double b = 0.03;
        constexpr double c = 2.43;
        constexpr double d = 0.59;
        constexpr double e = 0.14;
        return glm::clamp((in*(a*in+b))/(in*(c*in+d)+e), 0.0, 1.0);
    }

    // generate a random double between lower and upper (inclusive).
    inline double randFloat(double lower, double upper) {
        return lower+(upper-lower)*((double)std::rand()/(double)RAND_MAX);
    }

    // eta = η
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/refract.xhtml
    // Return a refraction vector using Snell's Law
    inline glm::dvec3 refract(glm::dvec3 incident, glm::dvec3 normal, double eta) {
        double cosTheta = glm::dot(incident, normal);
        double k = 1.0 - eta*eta * (1.0 - cosTheta*cosTheta);
        // If k < 0.0 then total internal reflection has occurred (eg light reflecting from water when looking up at the sea)
        if (k < 0.0)
            return glm::dvec3(0.0);
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
    inline double schlickApproximation(double cosTheta, double objectIOR, double surroundingIOR = 1.0) {
        // ((surroundingIOR - objectIOR) / (surroundingIOR + objectIOR)) squared
        double R0 = ((surroundingIOR - objectIOR) / (surroundingIOR + objectIOR));
        R0 *= R0;
        double x = 1.0-cosTheta; // x^5
        return R0 + (1.0 - R0)*(x*x*x*x*x);
    }


} // namespace Utils
