#include <iostream>
#include <raylib.h>
#include <cstring>
#include <cmath>

#include "field.hpp"
#include "ball.hpp"

#define LOG(x) std::cout << (x) << '\n';

int main(void) {
    srandom(time(nullptr));

    auto field = field_create();
    auto ball = ball_create();
    auto hole = hole_create();

    const double game_speed = 80;
    const auto field_size = 600;

    const auto width = 1280;
    const auto height = 720;

    const auto border_width = 2;
    const auto border_color = DARKGREEN;

    field->ball = ball;
    field->hole = hole;
    // field->border = {
    //     { (width - field_size) / 2, (height - field_size) / 2 },
    //     { (width - field_size) / 2 + field_size, (height - field_size) / 2 + field_size },
    // };

    field->border = {
        { (height - field_size) / 2, (height - field_size) / 2 },
        { (height - field_size) / 2 + field_size, (height - field_size) / 2 + field_size },
    };

    const Rectangle border_rectangle = {
        field->border.min.x - border_width,
        field->border.min.y - border_width,
        field->border.max.x - field->border.min.x + 2 * border_width,
        field->border.max.y - field->border.min.y + 2 * border_width,
    };

    ball->border = field->border;
    ball->speed = { 0, 0 };
    ball->position = {
        (ball->border.min.x + ball->border.max.x) / 2,
        (ball->border.min.y + ball->border.max.y) / 2,
    };
    ball->launch_speed = 1.1f;
    ball->friction = 0.99f;
    ball->radius = 5;
    ball->color = GREEN;

    hole->position = {
        random() % (int)(field_size - 2 * hole->radius - 2 * border_width) + hole->radius + field->border.min.x,
        random() % (int)(field_size - 2 * hole->radius - 2 * border_width) + hole->radius + field->border.min.y
    };
    hole->radius = ball->radius * 2;
    hole->color = BLACK;


    InitWindow(width, height, "2d golf");

    SetWindowState(FLAG_VSYNC_HINT);
    // SetWindowState(FLAG_WINDOW_RESIZABLE);

    int codepoints[512] = { 0 };
    for (int i = 0; i < 95; i++) codepoints[i] = 32 + i;   // Basic ASCII characters
    for (int i = 0; i < 255; i++) codepoints[96 + i] = 0x400 + i;   // Cyrillic characters

    const auto font32 = LoadFontEx(
        "resources/fonts/Roboto_Mono/static/RobotoMono-Regular.ttf",
        32,
        codepoints,
        512);

    SetExitKey(KEY_NULL);

    const double dt = 0.0001;
    double current_time = GetTime();
    double new_time;
    double frame_time;
    double accumulator = 0.0;

    int win_count = 0;
    auto buffer_template = "очки: ";
    Vector2 mouse_position;

    while (!WindowShouldClose()) {
        new_time = GetTime();
        frame_time = new_time - current_time;
        current_time = new_time;
        accumulator += frame_time;

        field_input(field);
        while (accumulator >= dt) {
            field_update(field, game_speed * dt);

            if (field->ball_in_hole) {
                hole->position.x = random() % (int)(field_size - 2 * hole->radius - 2 * border_width) + hole->radius + field->border.min.x;
                hole->position.y = random() % (int)(field_size - 2 * hole->radius - 2 * border_width) + hole->radius + field->border.min.y;
                hole->radius = ball->radius * 2;
                field->ball_in_hole = false;
                win_count++;
            }

            accumulator -= dt;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        /* render border */
        DrawRectangleLinesEx(border_rectangle, border_width, border_color);

        auto buffer = new char[std::strlen(buffer_template)];

        std::strcpy(buffer, buffer_template);
        std::snprintf(buffer + std::strlen(buffer), 5, "%d", win_count);

        DrawTextEx(
            font32,
            buffer,
            { border_rectangle.x + border_rectangle.width + border_width + 10, border_rectangle.y },
            32,
            0,
            BLACK
        );

        delete[] buffer;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            mouse_position = GetMousePosition();
            v2f mouse_distance = {
                ball->position.x - mouse_position.x,
                ball->position.y - mouse_position.y
            };

            if (ball->speed.x == 0 && ball->speed.y == 0) {
                Vector2 line_end = {
                    ball->position.x + mouse_distance.x,
                    ball->position.y + mouse_distance.y
                };

                auto max_line_length = 100;

                auto line_length = std::sqrt(std::pow(ball->position.x - GetMouseX(), 2) + std::pow(ball->position.y - GetMouseY(), 2));

                if (line_length > max_line_length) {
                    line_end.x = ball->position.x + mouse_distance.x / line_length * max_line_length;
                    line_end.y = ball->position.y + mouse_distance.y / line_length * max_line_length;
                }

                DrawLineEx(ball->position, line_end, 2, BLACK);
            }

        }

        field_render(field);

        EndDrawing();

        LOG(ball->position.x);
        LOG(ball->position.y);
        LOG(ball->speed.x);
        LOG(ball->speed.y);

    }

    UnloadFont(font32);

    CloseWindow();

    field_destroy(field);
    ball_destroy(ball);
    hole_destroy(hole);
}
