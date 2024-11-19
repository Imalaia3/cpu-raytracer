// Base class for all objects.
#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <string>

#include "../ray.h"

class Object {
public:
    struct CollisionData {
        std::string objectName;
        float t;
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };

    Object(glm::vec3 position, std::string objectName, glm::vec3 color) : m_position(position), m_name(objectName), m_color(color) {};
    virtual ~Object() = default;
    virtual std::optional<CollisionData> collides(Ray& ray) const = 0;

    glm::vec3 getPosition() const { return m_position; }
    void setPosition(glm::vec3 position) { m_position = position; }
    const std::string& getObjectName() const { return m_name; }
protected:
    std::string m_name;
    glm::vec3 m_position;
    glm::vec3 m_color;
};