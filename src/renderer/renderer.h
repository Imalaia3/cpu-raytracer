// Wrapper class that keeps all objects needed
// for rendering an image (camera, world, etc)
// and the global parameters. All settings
// should be changed by accessing the objects
// via the getters
#pragma once
#include <glm/glm.hpp>


class Renderer {
public:
    Renderer(uint32_t width, uint32_t height);
    std::vector<glm::vec3> render();
private:
    
};