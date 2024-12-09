#pragma once
#include "object.h"

// An object that wraps another object and makes it act as a volume (fog, mist, smoke, etc.)
// Volumetric lighting however will require ray marching
class VolumeObject : public Object {
public:
    VolumeObject(std::string objectName, std::unique_ptr<Object> volume, double density, std::shared_ptr<Material> material) : Object(glm::dvec3(.0), objectName, material), m_volume(std::move(volume)), m_volumeDensity(density) {}
    std::optional<Object::CollisionData> collides(Ray& ray, double threshold = 0.0) const override;
    double getDensity() const { return m_volumeDensity; }
private:
    std::unique_ptr<Object> m_volume;
    double m_volumeDensity;
};