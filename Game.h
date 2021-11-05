#pragma once

// #include "Bird.h"

// #include <optional>

// class Game {
//     private:
//         // static std::optional<Bird> bird;
//         Bird bird;
//         GLfloat bird_position[8];
//     public:
//         Game() = delete;
//         ~Game() = delete;

//         static void init(uint16_t window_width, uint16_t window_height);
//         // static void play();
//         bool is_ongoing();
//         void update();
//         void draw();
//         void clean_up();
//         void terminate();
// };



#include "Bird.h"

namespace Game {

    void init();

    bool is_ongoing();
    void update();
    void draw();
    void clean_up();
    void terminate();

}
