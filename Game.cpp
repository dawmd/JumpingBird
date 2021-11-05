// #include "Game.h"
// #include "Rectangle.h"
// #include <GL/glew.h>

// #include <iostream>

// static void init_bird_positions(GLfloat *positions, const GLfloat size) {
//     positions[0] = - size / 2.0f;
//     positions[1] = - size / 2.0f;
    
//     positions[2] =   size / 2.0f;
//     positions[3] = - size / 2.0f;
    
//     positions[4] =   size / 2.0f;
//     positions[5] =   size / 2.0f;
    
//     positions[6] = - size / 2.0f;
//     positions[7] =   size / 2.0f;
    
// }

// void Game::init(uint16_t window_width, uint16_t window_height) {
//     Window::init("Jumping Brd", window_height, window_width, true, false);
//     glewInit();
//     Rectangle::init_indices();
//     Rectangle::init_proj_matrix(window_width, window_height);

//     init_bird_positions(bird_position, 200.0f);
//     // bird = std::make_optional<Bird>({ bird_position, 0.0f });
//     bird = new Bird({ bird_position, 0.0f });
// }

// bool Game::is_ongoing() {
//     return Window::open();
// }

// // void Game::play() {
// //     auto fun = [&bird.value()]() { bird.update(0.05f, 0.05f, 0.0f); bird.rotate(0.5f), bird.draw();
// //     bird2.update(-0.1f, 0.05f, 0.0f); bird2.rotate(-0.5f), bird2.draw(); };
// //     Window::perform_while_open();
// // }

// void Game::update() {
//     constexpr float SPEED_UP = 0.5f;
//     constexpr float SPEED_DOWN = 0.25f;
//     constexpr float ANGLE_UP = 0.5f;
//     constexpr float ANGLE_DOWN = -0.25f;

//     if (Window::is_key_pressed('W') || Window::is_key_pressed(' ')) {
//         bird->update(SPEED_UP, 0.0f, 0.0f);
//         bird->rotate(ANGLE_UP);
//     }
//     else {
//         bird->update(SPEED_DOWN, 0.0f, 0.0f);
//         bird->rotate(ANGLE_DOWN);
//     }

//     // GLenum err;
//     // while ((err = glGetError()) != GL_NO_ERROR) {
//     //     std::cout << "ERROR\n";
//     // }
//     // std::cout << "\n\n";
// }

// void Game::draw() {
//     // bird.value().draw();
//     bird->draw();
// }

// void Game::clean_up() {
//     Window::clean_up();
//     glClear(GL_COLOR_BUFFER_BIT);
// }

// void Game::terminate() {
//     free(bird);
//     Window::remove();
// }

// GLfloat Game::bird_position[8] = {
//     0.0f, 0.0f,
//     0.0f, 0.0f,
//     0.0f, 0.0f,
//     0.0f, 0.0f
// };
// Bird *Game::bird;





// #include "Game.h"
// #include "Window.h"
// #include "Rectangle.h"
// #include <GL/glew.h>

// #include <iostream>

// static constexpr GLfloat bird_position[8] = {
    
// }

// static void init_bird_positions(GLfloat *positions, const GLfloat size) {
//     positions[0] = - size / 2.0f;
//     positions[1] = - size / 2.0f;
    
//     positions[2] =   size / 2.0f;
//     positions[3] = - size / 2.0f;
    
//     positions[4] =   size / 2.0f;
//     positions[5] =   size / 2.0f;
    
//     positions[6] = - size / 2.0f;
//     positions[7] =   size / 2.0f;
    
// }

// void Game::init(uint16_t window_width, uint16_t window_height) {
//     Window::init("Jumping Brd", window_height, window_width, true, false);
//     glewInit();
//     Rectangle::init_indices();
//     Rectangle::init_proj_matrix(window_width, window_height);

//     init_bird_positions(bird_position, 200.0f);
//     // bird = std::make_optional<Bird>({ bird_position, 0.0f });
//     bird = new Bird({ bird_position, 0.0f });
// }

// bool Game::is_ongoing() {
//     return Window::open();
// }

// // void Game::play() {
// //     auto fun = [&bird.value()]() { bird.update(0.05f, 0.05f, 0.0f); bird.rotate(0.5f), bird.draw();
// //     bird2.update(-0.1f, 0.05f, 0.0f); bird2.rotate(-0.5f), bird2.draw(); };
// //     Window::perform_while_open();
// // }

// void Game::update() {
//     constexpr float SPEED_UP = 0.5f;
//     constexpr float SPEED_DOWN = 0.25f;
//     constexpr float ANGLE_UP = 0.5f;
//     constexpr float ANGLE_DOWN = -0.25f;

//     if (Window::is_key_pressed('W') || Window::is_key_pressed(' ')) {
//         bird->update(SPEED_UP, 0.0f, 0.0f);
//         bird->rotate(ANGLE_UP);
//     }
//     else {
//         bird->update(SPEED_DOWN, 0.0f, 0.0f);
//         bird->rotate(ANGLE_DOWN);
//     }

//     // GLenum err;
//     // while ((err = glGetError()) != GL_NO_ERROR) {
//     //     std::cout << "ERROR\n";
//     // }
//     // std::cout << "\n\n";
// }

// void Game::draw() {
//     // bird.value().draw();
//     bird->draw();
// }

// void Game::clean_up() {
//     Window::clean_up();
//     glClear(GL_COLOR_BUFFER_BIT);
// }

// void Game::terminate() {
//     Window::remove();
// }




#include "Game.h"

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Window.h"

static void init_positions(GLfloat *positions, const float size) {
    positions[0] = - size / 2.0f;
    positions[1] = - size / 2.0f;

    positions[2] =   size / 2.0f;
    positions[3] = - size / 2.0f;

    positions[4] =   size / 2.0f;
    positions[5] =   size / 2.0f;

    positions[6] = - size / 2.0f;
    positions[7] =   size / 2.0f;
}

namespace Game {

    static struct {
        std::string window_title;
        uint16_t window_height;
        uint16_t window_width;
        bool resizable;
        bool centered;

        float bird_speed_up;
        float bird_speed_down;
        float bird_rotation_left;
        float bird_rotation_right;

        std::vector<char> jumping_keys;
    } GAME_PARAMETERS;

    static Bird *bird = nullptr;
    static GLfloat bird_position[8];

    /**
     * Initilizes the parameteres of the window and game.
     */
    static void init_parameteres() {
        // TODO: loading data from a JSON config file

        // Window
        GAME_PARAMETERS.window_title  = "Jumping Bird";
        GAME_PARAMETERS.window_height = 600;
        GAME_PARAMETERS.window_width  = 1000;
        GAME_PARAMETERS.resizable     = false;
        GAME_PARAMETERS.centered      = true;

        // Game
        GAME_PARAMETERS.bird_speed_up       =  0.5f;
        GAME_PARAMETERS.bird_speed_down     = -0.25f;
        GAME_PARAMETERS.bird_rotation_left  =  0.5f;
        GAME_PARAMETERS.bird_rotation_right = -0.25f;

        GAME_PARAMETERS.jumping_keys = { 'W', ' ' };
    }

    
    void init() {
        init_parameteres();

        Window::init(
            GAME_PARAMETERS.window_title,
            GAME_PARAMETERS.window_height,
            GAME_PARAMETERS.window_width,
            GAME_PARAMETERS.centered,
            GAME_PARAMETERS.resizable
        );

        glewInit();
        Rectangle::init_indices();
        Rectangle::init_proj_matrix(GAME_PARAMETERS.window_width, GAME_PARAMETERS.window_height);

        init_positions(bird_position, 200.0f);
        bird = new Bird({ bird_position, 0.0f });
    }

    bool is_ongoing() {
        return Window::open();
    }

    void update() {
        bool jump = false;

        for (char key : GAME_PARAMETERS.jumping_keys) {
            if (Window::is_key_pressed(key)) {
                jump = true;
                break;
            }
        }

        if (jump) {
            bird->update(GAME_PARAMETERS.bird_speed_up, 0.0f, 0.0f);
            bird->rotate(GAME_PARAMETERS.bird_rotation_right);
        }
        else {
            bird->update(GAME_PARAMETERS.bird_speed_down, 0.0f, 0.0f);
            bird->rotate(GAME_PARAMETERS.bird_rotation_left);
        }

        // GLenum err;
        // while ((err = glGetError()) != GL_NO_ERROR) {
        //     std::cout << "ERROR\n";
        // }
        // std::cout << "\n\n";
    }

    void draw() {
        bird->draw();
    }

    void clean_up() {
        Window::clean_up();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void terminate() {
        if (!bird) {
            delete bird;
        }
        Window::remove();
    }

}