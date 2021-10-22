#include "Window.h"

#include <iostream>

void Window::init(const std::string &title, uint16_t height, uint16_t width, bool centralised, bool resizable) {
    if (window) {
        std::cerr << "ERROR. Multiple windows are not accepted." << std::endl;
        return;
    }

    if (!glfwInit()) {
        std::cerr << "Error while initialising the GLFW library" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (height > vidmode->height || width > vidmode->width) {
        std::cerr << "ERROR. The resolution of the window is too big." << std::endl;
        std::exit(1);
    }
    else if (height < min_height || width < min_width) {
        std::cerr << "ERROR. The resolution of the window is too small." << std::endl;
        std::exit(1);
    }

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Creating the window has failed. Exiting the program." << std::endl;
        glfwTerminate();
        std::exit(1);
    }

    if (centralised) {
        glfwSetWindowPos(
            window,
            (vidmode->width - width) / 2,
            (vidmode->height - height) / 2
        );
    }
    else {
        glfwSetWindowPos(window, 0, 0);
    }

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Window::remove() {
    glfwTerminate();
}

void Window::clean_up() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::perform_while_open(const std::function<void()> &function) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        function();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *Window::window = nullptr;
uint16_t Window::height;
uint16_t Window::width;