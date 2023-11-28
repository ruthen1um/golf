#ifndef BALL_HPP
#define BALL_HPP

#include <raylib.h>

#include "types.hpp"

struct Ball {
    Box2D border;
    v2f speed;
    v2f position;
    float launch_speed;
    float friction;
    float radius;
    Color color;
};

Ball * ball_create(void);
void ball_destroy(Ball * ball);

void ball_input(Ball * ball);
void ball_update(Ball * ball, const double dt);
void ball_render(Ball * ball);

#endif
