#include "Game.h"
#include "Rectangle.h"
#include <GL/glew.h>

void Game::init(uint16_t window_width, uint16_t window_height) {
    Window::init("Jumping Brd", window_height, window_width, true, false);
    glewInit();
    Rectangle::init_indices();
    Rectangle::init_proj_matrix(window_width, window_height);
}