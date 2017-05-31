/* mapper_0.cpp - iNES mapper 0 (NROM) */

#include "mapper_0.h"


Mapper_0::Mapper_0(const NES2& nes2) :
    Mapper(nes2)
{
    /* Do checks here or something */
}


void Mapper_0::cart_write_byte(uint16_t addr, uint8_t byte)
{
    /* No support for PRG RAM yet, so nothing goes here */
}


uint8_t Mapper_0::cart_read_byte(uint16_t addr)
{
    /* No support for PRG RAM yet, so nothing from 0x6000 - 0x7FFF */

    /* If cart is NROM-128, mirror the first 16 KB */
    if ((addr >= 0x8000 && addr <= 0xBFFF) || cart.prg_pages == 1)
    {
        auto page = cart.prg_page_at(0);
        return page.at(addr & 0x3FFF);
    }
    else if (addr >= 0xC000)
    {
        auto page = cart.prg_page_at(1);
        return page.at(addr & 0x3FFF);
    }
}


void Mapper_0::cart_ppu_write_byte(uint16_t addr, uint8_t byte)
{
    /* No support for CHR RAM yet (not official but supported by most
     * emulators) */
}


uint8_t Mapper_0::cart_ppu_read_byte(uint16_t addr)
{
    auto page = cart.chr_page_at(0);
    return page.at(addr & 0x1FFF);
}
