#include "Window.h"

class Game {
    public:
        Game() = delete;
        ~Game() = delete;

        static void init(uint16_t window_width, uint16_t window_height);
        static void update();
        static void draw();
        static void clean_up();
};