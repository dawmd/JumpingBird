#pragma once

#include "Bird.h"

namespace Game {

    void init();

    bool is_ongoing();
    void update();
    void draw();
    void clean_up();
    void terminate();

}
