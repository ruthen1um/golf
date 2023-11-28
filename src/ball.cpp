#include <cmath>
#include <raylib.h>

#include "ball.hpp"

#define EPSILON 0.1f

Ball * ball_create(void) {
    auto ball = new Ball;
    return ball;
}

void ball_destroy(Ball * ball) {
    delete ball;
    ball = nullptr;
}

void ball_input(Ball * ball) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        auto mouse_position = GetMousePosition();
        v2f mouse_distance = {
            ball->position.x - mouse_position.x,
            ball->position.y - mouse_position.y
        };
        ball->speed.x = ball->launch_speed * mouse_distance.x * 0.1;
        ball->speed.y = ball->launch_speed * mouse_distance.y * 0.1;
    }
}

void ball_update(Ball * ball, const double dt) {
    /* left border check */
    if (ball->position.x < ball->border.min.x + ball->radius) {
        ball->speed.x = -ball->speed.x;
        ball->position.x = ball->border.min.x + ball->radius;
    }

    /* right border check */
    if (ball->position.x > ball->border.max.x - ball->radius) {
        ball->speed.x = -ball->speed.x;
        ball->position.x = ball->border.max.x - ball->radius;
    }

    /* top border check */
    if (ball->position.y < ball->border.min.y + ball->radius) {
        ball->speed.y = -ball->speed.y;
        ball->position.y = ball->border.min.y + ball->radius;
    }

    /* bottom border check */
    if (ball->position.y > ball->border.max.y - ball->radius) {
        ball->speed.y = -ball->speed.y;
        ball->position.y = ball->border.max.y - ball->radius;
    }

    ball->speed.x *= pow(ball->friction, dt);
    ball->speed.y *= pow(ball->friction, dt);

    ball->position.x += ball->speed.x * dt;
    ball->position.y += ball->speed.y * dt;

    if (fabs(ball->speed.x) < EPSILON) {
        ball->speed.x = 0;
    }

    if (fabs(ball->speed.y) < EPSILON) {
        ball->speed.y = 0;
    }
}

void ball_render(Ball * ball) {
    DrawCircleV(ball->position, ball->radius, ball->color);
}
