#include "volumetric.h"
#include "../utils/utils.h"

std::optional<VolumeObject::CollisionData> VolumeObject::collides(Ray& ray, float threshold) const {
    // https://en.wikipedia.org/wiki/Volumetric_path_tracing
    auto lowerBound = m_volume->collides(ray, 0.0f);
    if (!lowerBound.has_value())
        return {};

    // upperBound is the remaining distance from the initial collision to the other side of the volume (In a sphere that would be 2*radius)
    auto upperBound = m_volume->collides(ray, lowerBound.value().t+0.0001f);
    if (!upperBound.has_value())
        return {};
    
    lowerBound.value().t = glm::min(threshold, lowerBound.value().t);

    // this should never occur as we try to get the nearest possible collision and the farthest possible collision
    if (lowerBound.value().t >= upperBound.value().t)
        return {};

    // the distance between the two collisions, adjusted for the ray direction
    float length = ray.direction.length(); // do the sqrt only once
    // distance between entry and exit of the volume
    float distance = (upperBound.value().t - lowerBound.value().t) * length;
    // from RT in one weekend, it basically specifies the maximum possible distance the ray can go through
    // the volume before it hits a "particle". It's random but it is based off of the density. The higher
    // the density the lower the maxDistance. 
    float maxDistanceBeforeHit = (-1.0f / m_volumeDensity) * glm::log(Utils::randFloat(0.0f, 1.0f));

    // ray didn't "hit" anything.
    if (maxDistanceBeforeHit > distance)
        return {};
    
    float t = lowerBound.value().t + maxDistanceBeforeHit / length;
    return CollisionData {
        .objectName = m_name,
        .t = t,
        .position = ray.point(t),
        .normal = glm::vec3(),
        .material = m_material
    };
}