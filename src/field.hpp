#ifndef FIELD_HPP
#define FIELD_HPP

#include <raylib.h>

#include "ball.hpp"
#include "hole.hpp"
#include "types.hpp"

struct Field {
    Box2D border;
    Ball * ball;
    Hole * hole;
    bool ball_in_hole = false;
};

Field * field_create(void);
void field_destroy(Field * field);

void field_input(Field * field);
void field_update(Field * field, const double dt);
void field_render(Field * field);

#endif
