#include "renderer.h"

Renderer::Renderer(uint32_t width, uint32_t height) : m_displayWidth(width), m_displayHeight(height) {}

void Renderer::setCameraSettings(CameraSettings settings) {
    m_camera = Camera(settings.position, settings.fovDegrees,
        m_displayWidth, m_displayHeight, settings.samplesPerPixel
    );
    m_camera.setCameraBounceLimit(settings.maxBounces);
}

std::vector<glm::dvec3> Renderer::render() {
    return m_camera.render(m_world);
}