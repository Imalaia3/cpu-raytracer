#include "camera.h"
#include <iostream>
#include <limits>
#include "object/sphere.h"

#define LOG_VEC3(v) std::cout << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")\n"
#define LOG_VEC2(v) std::cout << "Vec2(" << v.x << ", " << v.y << ")\n"
#define PI 3.141592653589793

Camera::Camera(glm::dvec3 position, double fovDeg, uint32_t imgWidth, uint32_t imgHeight, uint32_t samplesPerPixel) :
    m_position(position), m_fovDeg(fovDeg), m_imageWidth(imgWidth), m_imageHeight(imgHeight), m_samplesPerPixel(samplesPerPixel) {
    
    // +y is up
    m_worldUp = glm::dvec3(0.0, 1.0, 0.0);
    // looking at +z
    m_camLookAt = glm::dvec3(0.0, 0.0, 1.0);
    calculateVectors();

    m_initialized = true;
}

void Camera::calculateVectors() {
    m_camForward = glm::normalize(m_camLookAt - m_position);
    m_camRight = glm::normalize(glm::cross(m_worldUp, m_camForward));
    m_camUp = glm::normalize(glm::cross(m_camForward, m_camRight));
}

std::vector<glm::dvec3> Camera::render(World& world) {
    if (!m_initialized)
        throw std::runtime_error("Camera has not been initialized!");

    std::vector<glm::dvec3> outputData(m_imageWidth*m_imageHeight, glm::dvec3(0.0));

    std::cout << "Camera: Maximum Bounces Per Pixel: " << m_maxBounces << "\n";

    glm::dvec2 pixelCoord(0.0);
    double planeDist = 1.0 / glm::tan(glm::radians(m_fovDeg) * 0.5);
    double aspectRatio = (double)m_imageWidth/m_imageHeight;
    double dX = 1.0/(double)m_imageWidth;
    double dY = 1.0/(double)m_imageHeight;
    for (uint32_t y = 0; y < m_imageHeight; y++) {
        // all rays should go through the center of each pixel and not the top left
        pixelCoord.y = (((double)y + 0.5) * dY) * 2.0 - 1.0;
        pixelCoord.y /= -aspectRatio;
        for (uint32_t x = 0; x < m_imageWidth; x++) {
            pixelCoord.x = (((double)x + 0.5) * dX) * 2.0 - 1.0;
            glm::dvec3 dir = glm::vec3(pixelCoord, planeDist);
            dir = glm::mat3(m_camRight, m_camUp, m_camForward) * dir;
            Ray ray(m_position, glm::normalize(dir));

            glm::dvec3 samplesSum = glm::dvec3(0.0);
            for (size_t i = 0; i < m_samplesPerPixel; i++) {
                samplesSum += getPixelValue(world, ray, m_maxBounces);
            }

            glm::dvec3 avgColor = Utils::toneMappingACES((samplesSum / static_cast<double>(m_samplesPerPixel))*m_exposure);
            outputData[y*m_imageWidth+x] = Utils::linearToSRGB(avgColor); // average of all pixels
        }
        // don't print on every line
        if (y % 20 == 0)
            std::cout << "Line " << y + 1 << " done (" << m_imageHeight - y - 1 << " lines left).\n";
    }

    return outputData;
}

std::optional<Object::CollisionData> Camera::getClosestObjectInWorld(Ray& ray, World& world) {
    double closestValue = std::numeric_limits<double>::max();
    Object::CollisionData closestCollision{};

    for (auto &&object : world.getObjects()) {
        auto c = object.get()->collides(ray, 0.0);
        if (c.has_value()) {
            if (c.value().t < closestValue && c.value().t > 0.0001) {
                closestValue = c.value().t;
                closestCollision = c.value();
            }
        }
    }
    if (closestValue == std::numeric_limits<double>::max())
        return {};
    return closestCollision;
}

glm::dvec3 Camera::getPixelValue(World& world, Ray initialRay, uint32_t bouncesLeft) {
    if (bouncesLeft == 0)
        return glm::dvec3(0.0);
    auto collision = getClosestObjectInWorld(initialRay, world);
    if (!collision.has_value()) // Sky color
        return glm::dvec3(0.529,0.807,0.921);
    auto mat = collision.value().material;
    auto newRay = mat->reflect(collision.value(), initialRay);
    return mat->color(collision.value(), newRay, getPixelValue(world, newRay, bouncesLeft-1));
}