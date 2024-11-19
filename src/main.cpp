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

    // Standard 480p 16:9 resolution
    const uint32_t WIDTH = 854;
    const uint32_t HEIGHT = 480;


    Screen scr(WIDTH, HEIGHT, "Raytracer");
    Renderer renderer(WIDTH, HEIGHT);
    renderer.setCameraSettings(Renderer::CameraSettings{
        .position = glm::vec3(0.0f),
        .focalLength = 1.f, // Around 50 deg ?
        .viewWidth = 2.0f * (16.0f/9.0f),
        .viewHeight = 2.0f, // 2 is an arbitrary value
    });

    // Used RT in one weekend object positions, so it's obvious when something is really wrong
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3(0.0f, 0.0f, 1.0f), 0.4f, "Ball", glm::vec3(1.0f)));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3(0.0f, -100.5f, 0.0f), 100.f, "Floor", glm::vec3(1.0f)));

    auto result = renderer.render();
    scr.fromArray(result);
    scr.updateDisplay();
    
    scr.waitForKeypress();
    return 0;
}
