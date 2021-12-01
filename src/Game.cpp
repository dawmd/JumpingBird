#include "Game.h"

// to get rid of (I'm going to use functors instead)
#include <GL/glew.h>

#include "Window.h"
#include "Bird.h"
#include "Pipe.h"

#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <cassert>

// For error messages
#include <iostream>
// For tangens
#include <cmath>

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

// static inline bool check_ptr(void *ptr) {
//     return ptr != nullptr;
// }

/** Returns a pseudo-random double number from the range [left_limit, right_limit] */
static inline double random_double(const double left_limit, const double right_limit) {
    assert(left_limit <= right_limit);
    return (static_cast<double>(std::rand()) / RAND_MAX) * (right_limit - left_limit) + left_limit;
}

namespace Game {


static bool continue_game = true;
static int leftmost_pipe_index = 0;
static int center_pipe_index = 0;

/*************************
 * 
 * Auxiliary structures
 * and functions
 * 
 ************************/


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
    float bird_max_rotation; // in degrees
    float bird_size; // the bird is a square whose side's lenght is equal to bird_size

    std::vector<char> jumping_keys;

    uint8_t pipe_pairs_number;
    float pipe_speed;
    uint16_t pipe_width;

    // A layer is how close to the player an object is (z coordinate)
    // It has to be within the range [-1.0f, 1.0f]
    float background_layer    =  0.0f;
    float pipe_layer          = -0.5f;
    float bird_layer          = -1.0f;
    float pipe_hole_ratio     =  2.5f;
    uint16_t pipe_break       =  250; // the break between consecutive pipes
    uint16_t starting_x_point;
} GAME_PARAMETERS;


struct PipePair {
    float center_point_height;
    Pipe upper_pipe;
    Pipe lower_pipe;

    PipePair(float center_point_height_, GLfloat *positions)
        : center_point_height(center_point_height_)
        , upper_pipe(positions)
        , lower_pipe(positions)
    {
        const float d_elevation = (static_cast<float>(GAME_PARAMETERS.window_height) + GAME_PARAMETERS.pipe_hole_ratio * GAME_PARAMETERS.bird_size) / 2.0f;
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

    // std::pair<float, float> get_border() const {
    //     return std::pair<float, float>(
    //             lower_pipe.get_x_coord() - GAME_PARAMETERS.pipe_width / 2,
    //             center_point_height - GAME_PARAMETERS.pipe_hole_ratio * GAME_PARAMETERS.bird_size
    //         );
    // }

    float get_x_coord() const {
        return upper_pipe.get_x_coord();
    }

    void reset() {
        upper_pipe.update(-upper_pipe.get_x_coord(), -upper_pipe.get_y_coord(), 0.0f);
        lower_pipe.update(-lower_pipe.get_x_coord(), -lower_pipe.get_y_coord(), 0.0f);

        const float d_elevation = (static_cast<float>(GAME_PARAMETERS.window_height) + GAME_PARAMETERS.pipe_hole_ratio * GAME_PARAMETERS.bird_size) / 2.0f;

        upper_pipe.update(0.0f, d_elevation, 0.0f);
        lower_pipe.update(0.0f, (-1.0f) * d_elevation, 0.0f);
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
    GAME_PARAMETERS.bird_speed_up       =  1.2f;
    GAME_PARAMETERS.bird_speed_down     = -0.7f;
    GAME_PARAMETERS.bird_rotation_left  =  0.5f;
    GAME_PARAMETERS.bird_rotation_right = -0.25f;
    GAME_PARAMETERS.bird_max_rotation   =  30.0f;
    GAME_PARAMETERS.bird_size           =  50.0f;

    GAME_PARAMETERS.jumping_keys = { 'W', ' ' };

    GAME_PARAMETERS.pipe_speed        = -1.5f;
    GAME_PARAMETERS.pipe_width        =  60;
    GAME_PARAMETERS.pipe_hole_ratio   =  2.5f;
    GAME_PARAMETERS.pipe_break        =  250;
    GAME_PARAMETERS.starting_x_point  =  GAME_PARAMETERS.window_width / 2;
    GAME_PARAMETERS.pipe_pairs_number =
        GAME_PARAMETERS.window_width / (GAME_PARAMETERS.pipe_width + GAME_PARAMETERS.pipe_break) + 3;
}


/*************************
 * 
 * Actual functionality
 * 
 ************************/


static double get_random_y_coord_of_pipes() {
    const double half_height = GAME_PARAMETERS.window_height / 2;
    return random_double(-half_height, half_height) * 0.7;
}

static void init_pipes() {
    const uint16_t total_x_movement = GAME_PARAMETERS.pipe_width + GAME_PARAMETERS.pipe_break;
    for (int i = 0; i < GAME_PARAMETERS.pipe_pairs_number; ++i) {
        pipe_pairs[i] = new PipePair(
            0.0f,
            pipe_position
        );
        if (!pipe_pairs[i]) {
            std::cerr << "An attempt to allocate memory has failed" << std::endl;
            std::exit(1);
        }
        pipe_pairs[i]->update(GAME_PARAMETERS.starting_x_point + total_x_movement * i, get_random_y_coord_of_pipes(), 0.0f);
    }
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

    init_positions(bird_position, GAME_PARAMETERS.bird_size, GAME_PARAMETERS.bird_size);
    bird = new Bird(bird_position, 0.0f);
    if (!bird) {
        std::cerr << "An attempt to allocate memory has failed" << std::endl;
        std::exit(1);
    }

    init_positions(pipe_position, GAME_PARAMETERS.pipe_width, GAME_PARAMETERS.window_height);
    pipe_pairs.resize(GAME_PARAMETERS.pipe_pairs_number);
    init_pipes();
}

bool is_ongoing() {
    return Window::open();
}

// // x1 < x2
// static void get_line(float x1, float y1, float x2, float y2) {
//     const float a = std::tan((y2 - y1) / (x2 - x1));
//     const float b = (y1 * x2 - x1 * y2) / (x2 - x1);

//     // y = ax + b
// }

    // static bool check_collisions() {
    //     // down-left corner of the "hole" between the pipes
    //     const std::pair<float, float> pipe_border = pipe_pairs[center_pipe_index]->get_border();
    //     const std::array<float, 4> hole_coords = {
    //         pipe_border.first, pipe_border.first + GAME_PARAMETERS.pipe_width,
    //         pipe_border.second, pipe_border.second + GAME_PARAMETERS.pipe_hole_ratio * GAME_PARAMETERS.bird_size
    //     };


    // }

static void update_pipes() {
    for (auto &pipe_pair : pipe_pairs) {
        pipe_pair->update(GAME_PARAMETERS.pipe_speed, 0.0f, 0.0f);
    }

    if (pipe_pairs[leftmost_pipe_index]->get_x_coord() < -(GAME_PARAMETERS.window_width + GAME_PARAMETERS.pipe_width)) {
        const int last_pipe_index = (leftmost_pipe_index + GAME_PARAMETERS.pipe_pairs_number - 1) % GAME_PARAMETERS.pipe_pairs_number;
        const float new_position = pipe_pairs[last_pipe_index]->get_x_coord() + GAME_PARAMETERS.pipe_break + GAME_PARAMETERS.pipe_width;
        pipe_pairs[leftmost_pipe_index]->reset();
        pipe_pairs[leftmost_pipe_index]->update(new_position, get_random_y_coord_of_pipes(), 0.0f);
        leftmost_pipe_index = (leftmost_pipe_index + 1) % GAME_PARAMETERS.pipe_pairs_number;
    }

    if (pipe_pairs[center_pipe_index]->get_x_coord() < -GAME_PARAMETERS.pipe_width / 2) {
        center_pipe_index = (center_pipe_index + 1) % GAME_PARAMETERS.pipe_pairs_number;
    }

    // if (check_collisions()) {
    //     continue_game = false;
    // }
}

void update() {
    if (!continue_game) {
        return;
    }

    update_pipes();

    bool jump = false;
    for (char key : GAME_PARAMETERS.jumping_keys) {
        if (Window::is_key_pressed(key)) {
            jump = true;
            break;
        }
    }

    if (jump) {
        bird->update(0.0f, GAME_PARAMETERS.bird_speed_up, 0.0f);
        const float d_angle =
            bird->get_angle() + GAME_PARAMETERS.bird_rotation_left > GAME_PARAMETERS.bird_max_rotation
                ? GAME_PARAMETERS.bird_max_rotation - bird->get_angle()
                : GAME_PARAMETERS.bird_rotation_left;
        bird->rotate(d_angle);
    }
    else {
        bird->update(0.0f, GAME_PARAMETERS.bird_speed_down, 0.0f);
        const float d_angle =
            bird->get_angle() + GAME_PARAMETERS.bird_rotation_right < (-1.0f) * GAME_PARAMETERS.bird_max_rotation
                ? (-1.0f) * GAME_PARAMETERS.bird_max_rotation - bird->get_angle()
                : GAME_PARAMETERS.bird_rotation_right;
        bird->rotate(d_angle);
    }
}

void draw() {
    for (auto &pipe_pair : pipe_pairs) {
        pipe_pair->draw();
    }
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

    for (auto &pipe_pair : pipe_pairs) {
        if (!pipe_pair) {
            delete pipe_pair;
        }
    }

    Window::remove();
}


} // namespace Game