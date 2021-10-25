#include "Game.h"
#include "Rectangle.h"
#include <GL/glew.h>

#include <iostream>

static void init_bird_positions(GLfloat *positions, const GLfloat size) {
    positions[0] = - size / 2.0f;
    positions[1] = - size / 2.0f;
    
    positions[2] =   size / 2.0f;
    positions[3] = - size / 2.0f;
    
    positions[4] =   size / 2.0f;
    positions[5] =   size / 2.0f;
    
    positions[6] = - size / 2.0f;
    positions[7] =   size / 2.0f;
    
}

void Game::init(uint16_t window_width, uint16_t window_height) {
    Window::init("Jumping Brd", window_height, window_width, true, false);
    glewInit();
    Rectangle::init_indices();
    Rectangle::init_proj_matrix(window_width, window_height);

    init_bird_positions(bird_position, 200.0f);
    // bird = std::make_optional<Bird>({ bird_position, 0.0f });
    bird = new Bird({ bird_position, 0.0f });
}

bool Game::is_ongoing() {
    return Window::open();
}

// void Game::play() {
//     auto fun = [&bird.value()]() { bird.update(0.05f, 0.05f, 0.0f); bird.rotate(0.5f), bird.draw();
//     bird2.update(-0.1f, 0.05f, 0.0f); bird2.rotate(-0.5f), bird2.draw(); };
//     Window::perform_while_open();
// }

void Game::update() {
    constexpr float speed_up = 0.5f;
    constexpr float speed_down = 0.25f;
    constexpr float angle_up = 0.5f;
    constexpr float angle_down = -0.25f;

    if (Window::is_key_pressed('W') || Window::is_key_pressed(' ')) {
        bird->update(speed_up, 0.0f, 0.0f);
        bird->rotate(angle_up);
    }
    else {
        bird->update(speed_down, 0.0f, 0.0f);
        bird->rotate(angle_down);
    }

    // GLenum err;
    // while ((err = glGetError()) != GL_NO_ERROR) {
    //     std::cout << "ERROR\n";
    // }
    // std::cout << "\n\n";
}

void Game::draw() {
    // bird.value().draw();
    bird->draw();
}

void Game::clean_up() {
    Window::clean_up();
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::terminate() {
    free(bird);
    Window::remove();
}

GLfloat Game::bird_position[8] = {
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f
};
Bird *Game::bird;