#include <iostream>
#include <memory>
#include "nes2.h"
#include "window.h"
#include "mappers/mapper_0.h"

using std::cout;
using std::endl;

static void dump_nes2(NES2& nes2)
{
    cout << "PRG ROM pages: " << +nes2.prg_pages << endl;
    cout << "CHR ROM pages: " << +nes2.chr_pages << endl;
    cout << "Mapper number: " << +nes2.mapper() << endl;
    cout << "Four-screen mode? " << nes2.flag_four_screen() << endl;
    cout << "Trainer ROM? " << nes2.flag_trainer() << endl;
    cout << "Battery-backed SRAM? " << nes2.flag_sram() << endl;
    cout << "Vertical VRAM mirroring? " << nes2.flag_vert_mirroring() << endl;
}

static void main_loop()
{
    bool running = true;
    WindowState state;

    while (running)
    {
        window_poll(state);

        if (state.window_closed)
        {
            window_close();
            running = false;
        }

        window_draw();
    }
}

int main(int argc, char **argv)
{
    NES2 nes2;
    std::unique_ptr<Mapper> map;

    if (argc == 2)
    {
        nes2.parse(argv[1]);
        map = std::make_unique<Mapper_0>(nes2);

        dump_nes2(nes2);
    }

    window_init();

    for (uint16_t x = 0; x < SCREEN_WIDTH; x++)
    {
        for (uint16_t y = 0; y < SCREEN_HEIGHT; y++)
        {
            window_render_pixel(x, y, 0);
        }
    }

    main_loop();

    return 0;
}
