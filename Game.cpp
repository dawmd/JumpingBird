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
        float bird_rotation_left; // in degrees
        float bird_rotation_right; // in degrees

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