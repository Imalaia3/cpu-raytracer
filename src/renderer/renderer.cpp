#include "renderer.h"

Renderer::Renderer(uint32_t width, uint32_t height) : m_displayWidth(width), m_displayHeight(height) {}

void Renderer::setCameraSettings(CameraSettings settings) {
    m_camera = Camera(settings.position, settings.focalLength,
        settings.viewWidth, settings.viewHeight,
        m_displayWidth, m_displayHeight
    );
}

std::vector<glm::vec3> Renderer::render() {
    return m_camera.render(); // todo: implement worlds
}