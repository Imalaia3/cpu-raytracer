#pragma once
#include "object.h"

// An object that wraps another object and makes it act as a volume (fog, mist, smoke, etc.)
// Volumetric lighting however will require ray marching
class VolumeObject : public Object {
public:
    VolumeObject(std::string objectName, std::unique_ptr<Object> volume, float density, std::shared_ptr<Material> material) : Object(glm::vec3(.0f), objectName, material), m_volume(std::move(volume)), m_volumeDensity(density) {}
    std::optional<Object::CollisionData> collides(Ray& ray, float threshold = 0.0f) const override;
    float getDensity() const { return m_volumeDensity; }
private:
    std::unique_ptr<Object> m_volume;
    float m_volumeDensity;
};