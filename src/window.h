/* render.h - SFML window interface */

#ifndef RENDER_H
#define RENDER_H

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

struct WindowState
{
    bool window_closed;

    bool direction_left;
    bool direction_up;
    bool direction_right;
    bool direction_down;
    bool button_a;
    bool button_b;
    bool button_start;
    bool button_select;

    WindowState() :
        window_closed(false),direction_left(false),direction_up(false),
        direction_right(false),direction_down(false),button_a(false),
        button_b(false),button_start(false),button_select(false)
    {}
};


void window_init();

void window_render_pixel(uint8_t x, uint8_t y, uint8_t color);

void window_draw();

void window_poll(WindowState& state);

void window_close();

#endif
