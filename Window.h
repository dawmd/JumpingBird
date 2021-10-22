#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

class Window {
    private:
        static GLFWwindow *window;
        static uint16_t height;
        static uint16_t width;
        static constexpr uint16_t min_height = 300;
        static constexpr uint16_t min_width = 300;
    public:
        Window() = delete;
        ~Window() = delete;

        static void init(const std::string &title, uint16_t height, uint16_t width, bool centralised, bool resizable);
        static void remove();
        static inline uint16_t get_height() {
            return height;
        }
        static inline uint16_t get_width() {
            return width;
        }
        static void perform_while_open(const std::function<void()> &function);
        static inline bool open() {
            return glfwWindowShouldClose(window);
        }
        static void clean_up();
};