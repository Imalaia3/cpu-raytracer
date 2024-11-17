#include "camera.h"

Camera::Camera(glm::vec3 position, float focalLength, float viewWidth, float viewHeight, uint32_t imgWidth, uint32_t imgHeight) :
    m_position(position), m_focalLength(focalLength), m_width(viewWidth), m_height(viewHeight) {
    
    m_pixelDx = viewWidth / imgWidth;
    m_pixelDy = -(viewHeight / imgHeight); // negative in order to have a positive Y coordinate system
    m_topLeft = m_position - glm::vec3(0.0f, 0.0f, m_focalLength) - glm::vec3(m_pixelDx, 0.0f, 0.0f) - glm::vec3(0.0f, m_pixelDy, 0.0f);
}
