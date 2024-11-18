#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>

class Screen {
public:
    Screen(uint32_t width, uint32_t height, const char* winTitle);
    ~Screen() {
        SDL_DestroyTexture(m_drawTexture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    // 0-255 range
    void putPixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue);
    // 0-1 range
    void putPixel(uint32_t x, uint32_t y, glm::vec3 color);
    void clearDisplay();
    void updateDisplay();
    // 0-1 range
    void fromArray(std::vector<glm::vec3>& pixels);
    
    void waitForKeypress();

    uint32_t getWidth() { return m_width; }
    uint32_t getHeight() { return m_height; }
    SDL_Window* getWindow() { return m_window; }
    SDL_Renderer* getRenderer() { return m_renderer; }

private:
    uint32_t m_width, m_height;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_drawTexture = nullptr;
};