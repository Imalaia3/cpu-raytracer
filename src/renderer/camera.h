#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 position, float focalLength, float viewWidth, float viewHeight, uint32_t imgWidth, uint32_t imgHeight);
    void render();
private:
    glm::vec3 m_position; // camera center
    float m_focalLength;
    float m_width, m_height; // only correlates with the aspect ratio of the display
    float m_pixelDx, m_pixelDy; // how much of viewWidth & -viewHeight (positive Y) correspond to display
    glm::vec3 m_topLeft; // top left corner of the camera.
};