#include <raylib.h>
#include "hole.hpp"

Hole * hole_create(void) {
    auto hole = new Hole;
    return hole;
}

void hole_destroy(Hole * hole) {
    delete hole;
    hole = nullptr;
}

void hole_render(Hole * hole) {
    DrawCircleV(hole->position, hole->radius, hole->color);
}
