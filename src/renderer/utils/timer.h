#pragma once
#include <chrono>

namespace Utils {
    class Timer {
    public:
        Timer() : m_running(false), m_hasBegunEver(false) {}
        bool isRunning() const { return m_running; }
        void start() {
            m_running = m_hasBegunEver = true;
            startPoint = std::chrono::high_resolution_clock::now();
        }
        void stop() {
            if (m_running) {
                m_running = false;
                endPoint = std::chrono::high_resolution_clock::now();
            }
        }
        void reset() {
            m_hasBegunEver = m_running = false;
        }
        void resume() {
            m_running = true;
        }
        std::chrono::duration<double> const getDelta() {
            if (m_hasBegunEver) return endPoint - startPoint;
            return {};
        }
    private:
        std::chrono::high_resolution_clock::time_point startPoint, endPoint;
        bool m_running = false;
        bool m_hasBegunEver = false;
    };
} // namespace Utils
