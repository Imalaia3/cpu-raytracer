#include "object.h"


void Object::setFaceType(CollisionData& collision, glm::dvec3 incomingRayDir) const {
    // if ray direction and normal vector are pointing in the same general direction then it's a back face
    // if it's a back face, flip the normal
    bool backFace = glm::dot(incomingRayDir, collision.normal) > 0.0;
    collision.faceType = backFace ? FaceType::BackFace : FaceType::FrontFace;
    collision.normal = backFace ? -collision.normal : collision.normal;
}