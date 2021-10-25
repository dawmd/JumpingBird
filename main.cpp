// // #ifndef GLEW_NO_GLU
// // #define GLEW_NO_GLU // cmake file
// // #endif

// #include "Window.h"
// #include "Rectangle.h"
// #include "Bird.h"
// // #include <GL/glew.h>
// // #include <GLFW/glfw3.h>


// #include <iostream>

// int main() {
//     Window::init(
//         "Cos",
//         500,
//         600,
//         true,
//         false
//     );

//     glewInit();

//     Rectangle::init_indices();
//     Rectangle::init_proj_matrix(600, 500);

//     const GLfloat vertices[8] = {
//         -200.0f, -150.0f,
//          200.0f, -150.0f,
//          200.0f,  150.0f,
//         -200.0f,  150.0f
//     };

//     const GLfloat vertices2[8] = {
//         -200.0f, -150.0f,
//          200.0f, -150.0f,
//          200.0f,  150.0f,
//         -200.0f,  150.0f
//     };

//     Bird bird(vertices, 0.0f);

//     Bird bird2(vertices2, 0.0f);
//     // GLenum err;

//     // while (!Window::open()) {
//     //     glClear(GL_COLOR_BUFFER_BIT);
//     //     bird.update(0.05f, 0.05f, 0.0f);
//     //     bird.rotate(0.5f);
//     //     bird.draw();
//     //     bird2.update(-0.05f, -0.05f, 0.0f);
//     //     bird2.rotate(-0.1f);
//     //     bird2.draw();
//     //     Window::clean_up();
//     //     while ((err = glGetError()) != GL_NO_ERROR) {
//     //         std::cerr << "ERROR\n";
//     //     }
//     // }

//     auto fun = [&bird, &bird2]() { bird.update(0.05f, 0.05f, 0.0f); bird.rotate(0.5f), bird.draw();
//     bird2.update(-0.1f, 0.05f, 0.0f); bird2.rotate(-0.5f), bird2.draw(); };

//     Window::perform_while_open(fun);

//     Window::remove();

//     return 0;
// }

#include "Game.h"

int main() {
    Game::init(1800, 800);
    while (Game::is_ongoing()) {
        Game::update();
        Game::draw();
        Game::clean_up();
    }
    Game::terminate();
    return 0;
}