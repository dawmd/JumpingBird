#include "Game.h"

#include <GL/glew.h>

#include "Window.h"
#include "Bird.h"
#include "Pipe.h"

#include <string>
#include <vector>

static void init_positions(GLfloat *positions, const float width, const float height) {
    positions[0] = - width / 2.0f;
    positions[1] = - height / 2.0f;

    positions[2] =   width / 2.0f;
    positions[3] = - height / 2.0f;

    positions[4] =   width / 2.0f;
    positions[5] =   height / 2.0f;

    positions[6] = - width / 2.0f;
    positions[7] =   height / 2.0f;
}

namespace Game {

    // TODO: add default values
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

        uint8_t pipe_pairs_number;
    } GAME_PARAMETERS;


    struct PipePair {
        Pipe upper_pipe;
        Pipe lower_pipe;
        float center_point_height;

        PipePair(float center_point_height_, GLfloat *positions, float pipe_hole_size)
            : center_point_height(center_point_height_)
            , upper_pipe(positions)
            , lower_pipe(positions)
        {
            const float d_elevation = (static_cast<float>(GAME_PARAMETERS.window_height) + pipe_hole_size) / 2.0f;
            upper_pipe.update(0.0f, d_elevation, 0.0f);
            lower_pipe.update(0.0f, (-1.0f) * d_elevation, 0.0f);
        }

        void update(float dx, float dy, float dz) {
            lower_pipe.update(dx, dy, dz);
            upper_pipe.update(dx, dy, dz);
        }

        void draw() {
            lower_pipe.draw();
            upper_pipe.draw();
        }
    };


    static Bird *bird = nullptr;
    static std::vector<PipePair*> pipe_pairs;
    static GLfloat bird_position[8];
    static GLfloat pipe_position[8];

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

        GAME_PARAMETERS.pipe_pairs_number = /* computing based on the window's size */ 1;
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

        init_positions(bird_position, 200.0f, 200.0f);
        bird = new Bird({ bird_position, 0.0f });

        init_positions(pipe_position, 50.0f, GAME_PARAMETERS.window_height);
        pipe_pairs.resize(GAME_PARAMETERS.pipe_pairs_number);
        for (uint8_t i = 0; i < GAME_PARAMETERS.pipe_pairs_number; ++i) {
            pipe_pairs[i] = new PipePair(0.0f, pipe_position, 40.0f);
        }
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
        for (auto &pipe_pair : pipe_pairs) {
            pipe_pair->draw();
        }
    }

    void clean_up() {
        Window::clean_up();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void terminate() {
        if (!bird) {
            delete bird;
        }
        for (auto &pipe_pair : pipe_pairs) {
            if (!pipe_pair) {
                delete pipe_pair;
            }
        }
        Window::remove();
    }

} // namespace Game