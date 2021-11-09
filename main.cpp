#include "Game.h"

int main() {
    Game::init();
    while (Game::is_ongoing()) {
        Game::update();
        Game::draw();
        Game::clean_up();
    }
    Game::terminate();
    return 0;
}