#include "camera.h"
#include <iostream>
#include <limits>
#include "object/sphere.h"

Camera::Camera(glm::vec3 position, float focalLength, float viewWidth, float viewHeight, uint32_t imgWidth, uint32_t imgHeight) :
    m_position(position), m_focalLength(focalLength), m_width(viewWidth), m_height(viewHeight), m_imageWidth(imgWidth), m_imageHeight(imgHeight) {
    
    m_pixelDx = viewWidth / (float)imgWidth;
    m_pixelDy = -(viewHeight / (float)imgHeight);
    // +z is forward
    m_topLeft = m_position + glm::vec3(0.0f, 0.0f, m_focalLength) - glm::vec3(viewWidth/2.0f, 0.0f, 0.0f) - glm::vec3(0.0f, -viewHeight/2.0f, 0.0f);
    m_initialized = true;
}

std::vector<glm::vec3> Camera::render(World& world) {
    if (!m_initialized)
        throw std::runtime_error("Camera has not been initialized!");

    std::vector<glm::vec3> outputData(m_imageWidth*m_imageHeight, glm::vec3(0.0f));

    // all rays should go through the center of each pixel and not the top left
    glm::vec3 drawOrigin = m_topLeft + (glm::vec3(m_pixelDx, m_pixelDy, 0.0f) * 0.5f);
    std::cout << "Camera: Screen Pixel Origin (XYZ): " << drawOrigin.x << " " << drawOrigin.y << " " << drawOrigin.z << "\n";
    for (uint32_t y = 0; y < m_imageHeight; y++) {
        for (uint32_t x = 0; x < m_imageWidth; x++) {
            // pixel position - camera center, resulting in a coordinate system where:
            // left = -x, right = +x, up = +y down = -y
            // fixme: maybe it's better if +y to be up
            glm::vec3 direction = (drawOrigin + glm::vec3(x*m_pixelDx, y*m_pixelDy, 0.0f)) - m_position;
            Ray ray(m_position, glm::normalize(direction));

            // std::cout << "Direction at: "  << x << " " << y;
            // std::cout << " : "  <<  glm::normalize(direction).x << " " << glm::normalize(direction).y << glm::normalize(direction).z << "\n";

            auto col = getClosestObjectInWorld(ray, world);
            if (col.has_value()) {
                // https://docs.unity3d.com/Packages/com.unity.render-pipelines.universal@8.3/manual/writing-shaders-urp-unlit-normals.html
                outputData[y*m_imageWidth+x] = col.value().normal * 0.5f + 0.5f;
            } else {
                outputData[y*m_imageWidth+x] = glm::vec3(0.529f,0.807f,0.921f);
            }
        }
    }

    return outputData;
}

std::optional<Object::CollisionData> Camera::getClosestObjectInWorld(Ray& ray, World& world) {
    float closestValue = std::numeric_limits<float>::max();
    Object::CollisionData closestCollision{};

    for (auto &&object : world.getObjects()) {
        auto c = object.get()->collides(ray);
        if (c.has_value()) {
            if (c.value().t < closestValue && c.value().t >= 0.0f) {
                closestValue = c.value().t;
                closestCollision = c.value();
            }
        }
    }
    if (closestValue == std::numeric_limits<float>::max())
        return {};
    return closestCollision;
}