/* window.cpp - SFML window interface */

#include <cstdio>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "window.h"

std::unique_ptr<sf::RenderWindow> window;
std::unique_ptr<sf::Image> screen;
std::unique_ptr<sf::Texture> screen_tex;
std::unique_ptr<sf::Sprite> screen_sprite;

/* No NTSC video decoding yet */
uint8_t palette[] =
{
    84,    84,    84,    /* 00 */
    0,     30,    116,   /* 01 */
    8,     16,    144,   /* 02 */
    48,    0,     136,   /* 03 */
    68,    0,     100,   /* 04 */
    92,    0,     48,    /* 05 */
    84,    4,     0,     /* 06 */
    60,    24,    0,     /* 07 */
    32,    42,    0,     /* 08 */
    8,     58,    0,     /* 09 */
    0,     64,    0,     /* 0A */
    0,     60,    0,     /* 0B */
    0,     50,    60,    /* 0C */
    0,     0,     0,     /* 0D */
    0,     0,     0,     /* 0E */
    0,     0,     0,     /* 0F */
    152,   150,   152,   /* 10 */
    8,     76,    196,   /* 11 */
    48,    50,    236,   /* 12 */
    92,    30,    228,   /* 13 */
    136,   20,    176,   /* 14 */
    160,   20,    100,   /* 15 */
    152,   34,    32,    /* 16 */
    120,   60,    0,     /* 17 */
    84,    90,    0,     /* 18 */
    40,    114,   0,     /* 19 */
    8,     124,   0,     /* 1A */
    0,     118,   40,    /* 1B */
    0,     102,   120,   /* 1C */
    0,     0,     0,     /* 1D */
    0,     0,     0,     /* 1E */
    0,     0,     0,     /* 1F */
    236,   238,   236,   /* 20 */
    76,    154,   236,   /* 21 */
    120,   124,   236,   /* 22 */
    176,   98,    236,   /* 23 */
    228,   84,    236,   /* 24 */
    236,   88,    180,   /* 25 */
    236,   106,   100,   /* 26 */
    212,   136,   32,    /* 27 */
    160,   170,   0,     /* 28 */
    116,   196,   0,     /* 29 */
    76,    208,   32,    /* 2A */
    56,    204,   108,   /* 2B */
    56,    180,   204,   /* 2C */
    60,    60,    60,    /* 2D */
    0,     0,     0,     /* 2E */
    0,     0,     0,     /* 2F */
    236,   238,   236,   /* 30 */
    168,   204,   236,   /* 31 */
    188,   188,   236,   /* 32 */
    212,   178,   236,   /* 33 */
    236,   174,   236,   /* 34 */
    236,   174,   212,   /* 35 */
    236,   180,   176,   /* 36 */
    228,   196,   144,   /* 37 */
    204,   210,   120,   /* 38 */
    180,   222,   120,   /* 39 */
    168,   226,   144,   /* 3A */
    152,   226,   180,   /* 3B */
    160,   214,   228,   /* 3C */
    160,   162,   160,   /* 3D */
    0,     0,     0,     /* 3E */
    0,     0,     0,     /* 3F */
};


void window_init()
{
    auto mode = sf::VideoMode(800, 600);

    window = std::make_unique<sf::RenderWindow>(mode, "YANE");
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    screen = std::make_unique<sf::Image>();
    screen->create(SCREEN_WIDTH, SCREEN_HEIGHT);

    screen_tex = std::make_unique<sf::Texture>();
    screen_tex->create(SCREEN_WIDTH, SCREEN_HEIGHT);

    screen_sprite = std::make_unique<sf::Sprite>(*screen_tex);
}

void window_render_pixel(uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t red = palette[(color % 0x3F) * 3];
    uint8_t green = palette[(color % 0x3F) * 3 + 1];
    uint8_t blue = palette[(color % 0x3F) * 3 + 2];

    screen->setPixel(x, y, sf::Color(red, green, blue));
}

void window_draw()
{
    window->clear();

    screen_tex->update(*screen);
    window->draw(*screen_sprite);

    window->display();
}

void window_poll(WindowState& state)
{
    /* I'll probably make it more sophisticated in the future, but this works */
    sf::Event e;
    while (window->pollEvent(e))
    {
        if (e.type == sf::Event::KeyPressed)
        {
            switch(e.key.code)
            {
            case sf::Keyboard::Left:
                state.direction_left = true;
                break;
            case sf::Keyboard::Up:
                state.direction_up = true;
                break;
            case sf::Keyboard::Right:
                state.direction_right = true;
                break;
            case sf::Keyboard::Down:
                state.direction_down = true;
                break;
            case sf::Keyboard::Z:
                state.button_b = true;
                break;
            case sf::Keyboard::X:
                state.button_a = true;
                break;
            case sf::Keyboard::Return:
                state.button_start = true;
                break;
            case sf::Keyboard::BackSlash:
                state.button_select = true;
                break;
            case sf::Keyboard::Escape:
                state.window_closed = true;
                break;
            }
        }

        if (e.type == sf::Event::KeyReleased)
        {
            switch(e.key.code)
            {
            case sf::Keyboard::Left:
                state.direction_left = false;
                break;
            case sf::Keyboard::Up:
                state.direction_up = false;
                break;
            case sf::Keyboard::Right:
                state.direction_right = false;
                break;
            case sf::Keyboard::Down:
                state.direction_down = false;
                break;
            case sf::Keyboard::Z:
                state.button_b = false;
                break;
            case sf::Keyboard::X:
                state.button_a = false;
                break;
            case sf::Keyboard::Return:
                state.button_start = false;
                break;
            case sf::Keyboard::BackSlash:
                state.button_select = false;
                break;
            }
        }
    }
}

void window_close()
{
    window->close();
}
