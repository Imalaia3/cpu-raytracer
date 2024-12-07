#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "display/screen.h"
#include "renderer/renderer.h"
#include "renderer/object/sphere.h"
#include "renderer/object/plane.h"
#include "renderer/object/volumetric.h"
#include "renderer/object/triangle.h"
#include "renderer/material/generic.h"
#include "renderer/material/constant.h"
#include "renderer/utils/timer.h"

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
        .maxBounces = 24,
        .samplesPerPixel = 2
    });

    auto whiteDiffuse = std::make_shared<GenericDiffuse>();
    auto yellowEmmisive = std::make_shared<GenericDiffuse>();
    yellowEmmisive->updateSettings(Utils::colorFromHex(0xf79900)*4.0f, Utils::colorFromHex(0xf79900), 0.5f);
    auto smokeMaterial = std::make_shared<ConstantMaterial>();
    smokeMaterial->updateSettings(glm::vec3(0.2f));
    auto redDiffuse = std::make_shared<GenericDiffuse>();
    redDiffuse->updateSettings(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);

    auto greenDiffuse = std::make_shared<GenericDiffuse>();
    greenDiffuse->updateSettings(glm::vec3(0.0f), Utils::colorFromHex(0x3f9b0b), 0.5f);

    //  renderer.getWorld().addObject(std::make_unique<VolumeObject>("", std::make_unique<Sphere>(glm::vec3(-2.0f, 0.0f, 5.0f), 0.5f, "Bob0", whiteDiffuse), 0.1f, smokeMaterial));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( -1.0f, -.5f, 3.0f), 0.5f, "Bob1", yellowEmmisive));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( 2.0f, 0.0f, 3.0f), 0.5f, "Bob2", whiteDiffuse));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::vec3( 0.5f, 0.0f, 6.5f), 0.5f, "Bob3", redDiffuse));
    renderer.getWorld().addObject(std::make_unique<Plane>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), "Floor", whiteDiffuse));
    renderer.getWorld().addObject(std::make_unique<Triangle>(
        glm::vec3(0.0f, .5f, 6.0f),
        glm::vec3(0.0f, -0.5f, 5.0f),
        glm::vec3(1.0f, -0.5f, 5.0f),
    "Triangle", greenDiffuse));

    Utils::Timer perfTimer;
    perfTimer.start();
    auto result = renderer.render();
    scr.fromArray(result);
    scr.updateDisplay();
    perfTimer.stop();
    auto deltaTime = perfTimer.getDelta();
    std::cout << "Image complete!\n";
    std::cout << "Render Info:\n";
    std::cout << "\tImage size: " << WIDTH << "x" << HEIGHT << " pixels\n";
    std::cout << "\tObjects in world: " << renderer.getWorld().objectCount() << "\n";
    std::cout << "\tRendering & Presenting took " << std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() << "ms.\n";
    std::cout << "Press any key twice to exit\n";

    scr.waitForKeypress();
    SDL_Delay(500);
    scr.waitForKeypress();
    return 0;
}
