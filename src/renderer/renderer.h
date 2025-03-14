// Wrapper class that keeps all objects needed
// for rendering an image (camera, world, etc)
// and the global parameters. All settings
// should be changed by accessing the objects
// via the getters
#pragma once
#include <glm/glm.hpp>

#include "camera.h"
#include "world.h"

class Renderer {
public:
    //todo: should this be moved into Camera so the camera can take this in the constructor?
    struct CameraSettings {
        glm::dvec3 position;
        double fovDegrees;
        uint32_t maxBounces;
        uint32_t samplesPerPixel;
    };

    Renderer(uint32_t width, uint32_t height);
    std::vector<glm::dvec3> render();
    
    void setCameraSettings(CameraSettings settings);
    World& getWorld() { return m_world; }
    void setRenderCallback(std::function<void(const std::vector<glm::dvec3>&)> cb) {
        m_camera.setCallback(cb);
    }
private:
    uint32_t m_displayWidth, m_displayHeight;
    Camera m_camera;
    World m_world;
};