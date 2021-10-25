#include "Window.h"
#include "Bird.h"

#include <optional>

class Game {
    private:
        // static std::optional<Bird> bird;
        static Bird *bird;
        static GLfloat bird_position[8];
    public:
        Game() = delete;
        ~Game() = delete;

        static void init(uint16_t window_width, uint16_t window_height);
        // static void play();
        static bool is_ongoing();
        static void update();
        static void draw();
        static void clean_up();
        static void terminate();
};