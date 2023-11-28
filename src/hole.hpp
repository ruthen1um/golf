#ifndef HOLE_HPP
#define HOLE_HPP

#include <raylib.h>

#include "types.hpp"

struct Hole {
    v2f position;
    float radius;
    Color color;
};

Hole * hole_create(void);
void hole_destroy(Hole * hole);

void hole_render(Hole * hole);

#endif
