#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "display/screen.h"
#include "renderer/renderer.h"
#include "renderer/object/sphere.h"

int main(int argc, char const *argv[]) {   
    SDL_version ver; SDL_VERSION(&ver);
    std::cout << "SDL2 Version: " << (uint32_t)ver.major << "." << (uint32_t)ver.minor << "\n";
    std::cout << "GLM Version: " << GLM_VERSION << "\n";

    // 16:9 resolution
    const uint32_t WIDTH = 960;
    const uint32_t HEIGHT = 540;


    Screen scr(WIDTH, HEIGHT, "Raytracer");
    Renderer renderer(WIDTH, HEIGHT);
    renderer.setCameraSettings(Renderer::CameraSettings{
        .position = glm::vec3(0.0f),
        .focalLength = 1.f,
        .viewWidth = 1.6f,
        .viewHeight = 0.9f,
        .maxBounces = 16
    });

    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3(-2.0f, 0.0f, 3.0f), 0.5f, "Bob0", glm::vec3(1.0f)));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( 0.0f, -.5f, 3.0f), 0.5f, "Bob1", glm::vec3(1.0f)));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( 2.0f, 0.0f, 3.0f), 0.5f, "Bob2", glm::vec3(1.0f)));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( 2.0f, -100.0f, 15.0f), 99.5f, "Floor", glm::vec3(1.0f, 1.0f, 0.0f)));

    auto result = renderer.render();
    scr.fromArray(result);
    scr.updateDisplay();
    
    scr.waitForKeypress();
    return 0;
}
