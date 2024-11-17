#include "screen.h"
#include <stdexcept>
#include <iostream>

Screen::Screen(uint32_t width, uint32_t height, const char* winTitle) : m_width(width), m_height(height) {
    m_window = SDL_CreateWindow(winTitle,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        0
    );
    if (!m_window) {
        throw std::runtime_error("Failed to create an SDL window!");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        throw std::runtime_error("Failed to create an SDL renderer!");
    }

    m_drawTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
    if (!m_drawTexture) {
        throw std::runtime_error("Failed to create an SDL texture!");
    }

}

void Screen::putPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue) {
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, 255);
    SDL_RenderDrawPoint(m_renderer, x, y);
}
void Screen::putPixel(uint32_t x, uint32_t y, glm::vec3 color) {
    SDL_SetRenderDrawColor(m_renderer,
        floor(color.r >= 1.0 ? 255 : color.r * 256.0),
        floor(color.g >= 1.0 ? 255 : color.g * 256.0),
        floor(color.b >= 1.0 ? 255 : color.b * 256.0),
        255
    );
    SDL_RenderDrawPoint(m_renderer, x, y);
}
void Screen::clearDisplay() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}
void Screen::updateDisplay() {
    SDL_RenderPresent(m_renderer);
}

void Screen::fromArray(std::vector<glm::vec3>& pixels) {
    void* pixelPtr = nullptr;
    int pitch = 0;
    SDL_LockTexture(m_drawTexture, NULL, &pixelPtr, &pitch);
    Uint32* surfPixels = (uint32_t*)pixelPtr;
    for (size_t y = 0; y < m_height; y++) {
        for (size_t x = 0; x < m_width; x++) {
            uint8_t r = floor(pixels[y*m_width+x].r >= 1.0 ? 255 : pixels[y*m_width+x].r * 256.0);
            uint8_t g = floor(pixels[y*m_width+x].g >= 1.0 ? 255 : pixels[y*m_width+x].g * 256.0);
            uint8_t b = floor(pixels[y*m_width+x].b >= 1.0 ? 255 : pixels[y*m_width+x].b * 256.0);
            surfPixels[y*m_width+x] = (r << 24) | (g << 16) | (b << 8) | 255;
        }
    }
    SDL_UnlockTexture(m_drawTexture);
    SDL_RenderCopy(m_renderer, m_drawTexture, NULL, NULL);
}