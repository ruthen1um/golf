#include <cmath>
#include <raylib.h>

#include "field.hpp"

Field * field_create(void) {
    auto field = new Field;
    return field;
}

void field_destroy(Field * field) {
    delete field;
    field = nullptr;
}

void field_input(Field * field) {
    if (field->ball->speed.x != 0 || field->ball->speed.y != 0) {
        return;
    }
    ball_input(field->ball);
}

void field_update(Field * field, const double dt) {
    ball_update(field->ball, dt);

    if (field->hole->position.x - field->hole->radius <= field->ball->position.x - field->ball->radius && \
        field->hole->position.x + field->hole->radius >= field->ball->position.x + field->ball->radius && \
        field->hole->position.y - field->hole->radius <= field->ball->position.y - field->ball->radius && \
        field->hole->position.y + field->hole->radius >= field->ball->position.y + field->ball->radius) {
        field->ball_in_hole = true;
    }
}

void field_render(Field * field) {
    ball_render(field->ball);
    hole_render(field->hole);
}
