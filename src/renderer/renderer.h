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
    //todo: should this be move into Camera so the camera can take this in the constructor?
    struct CameraSettings {
        glm::vec3 position;
        float focalLength;
        float viewWidth;
        float viewHeight;
        uint32_t maxBounces;
        uint32_t samplesPerPixel;
    };

    Renderer(uint32_t width, uint32_t height);
    std::vector<glm::vec3> render();
    
    void setCameraSettings(CameraSettings settings);
    World& getWorld() { return m_world; }
private:
    uint32_t m_displayWidth, m_displayHeight;
    Camera m_camera;
    World m_world;
};