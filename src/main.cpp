#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>

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

    srand(static_cast<unsigned int>(time(0)));

    // 16:9 resolution
    const uint32_t WIDTH = 960;
    const uint32_t HEIGHT = 540;

    Screen scr(WIDTH, HEIGHT, "Raytracer");
    Renderer renderer(WIDTH, HEIGHT);
    renderer.setCameraSettings(Renderer::CameraSettings{
        .position = glm::dvec3(0.0, 0.0, 0.0),
        .fovDegrees = 90.0,
        .maxBounces = 24,
        .samplesPerPixel = 10
    });

    renderer.setRenderCallback([&](const std::vector<glm::dvec3>& pixels){
        scr.fromArray(pixels);
        scr.updateDisplay();
    });

    auto whiteDiffuse = std::make_shared<GenericDiffuse>();
    auto yellowEmmisive = std::make_shared<GenericDiffuse>();
    yellowEmmisive->updateSettings(Utils::colorFromHex(0xf79900)*4.0, Utils::colorFromHex(0xf79900), 0.5);
    auto smokeMaterial = std::make_shared<ConstantMaterial>();
    smokeMaterial->updateSettings(glm::dvec3(0.2));
    auto redDiffuse = std::make_shared<GenericDiffuse>();
    redDiffuse->updateSettings(glm::dvec3(0.0), glm::dvec3(1.0, 0.0, 0.0), 0.5);
    auto greenDiffuse = std::make_shared<GenericDiffuse>();
    greenDiffuse->updateSettings(glm::dvec3(0.0), glm::dvec3(0.0, 1.0, 0.0), 0.5);


    //  renderer.getWorld().addObject(std::make_unique<VolumeObject>("", std::make_unique<Sphere>(glm::dvec3(-2.0, 0.0, 5.0), 0.5, "Bob0", whiteDiffuse), 0.1, smokeMaterial));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::dvec3( -1.0, 0.0, 3.0), 0.5, "Bob1", yellowEmmisive));
    renderer.getWorld().addObject(std::make_unique<Sphere>(glm::dvec3( 1.1, 0.0, 3.0), 0.5, "Bob3", redDiffuse));
    renderer.getWorld().addObject(std::make_unique<Triangle>(
        glm::dvec3(0.0, .5, 6.0),
        glm::dvec3(0.0, -0.5, 5.0),
        glm::dvec3(1.0, -0.5, 5.0),
    "Triangle", greenDiffuse));
    renderer.getWorld().addObject(std::make_unique<Plane>(glm::dvec3(0.0, 1.0, 0.0), glm::dvec3(0.0, -1.0, 0.0), "Floor", whiteDiffuse));

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
