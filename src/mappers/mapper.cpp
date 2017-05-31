/* mapper.cpp - Memory Mapper Base Class */

#include <memory>
#include <stdexcept>
#include <vector>

#include "mapper.h"


Mapper::Mapper(const NES2& nes2) :
    cart(nes2)
{
}


void Mapper::write_byte(uint16_t addr, uint8_t byte)
{
    if (addr <= 0x1FFF)
    {
        internal_ram.at(addr & 0x07FF) = byte;
    }
    else if (addr >= 0x2000 && addr <= 0x2007)
    {
        /* PPU registers */
    }
    else if (addr >= 0x2008 && addr <= 0x3FFF)
    {
        /* Mirrors of PPU registers */
    }
    else if (addr >= 0x4000 && addr <= 0x4017)
    {
        /* APU and IO registers */
    }
    else if (addr >= 0x4018 && addr <= 0x401F)
    {
        /* Disabled APU and IO functionality */
    }
    else if (addr >= 0x4020)
    {
        cart_write_byte(addr, byte);
    }
}


uint8_t Mapper::read_byte(uint16_t addr)
{
    if (addr <= 0x1FFF)
    {
        return internal_ram.at(addr & 0x07FF);
    }
    else if (addr >= 0x2000 && addr <= 0x2007)
    {
        /* PPU registers */
    }
    else if (addr >= 0x2008 && addr <= 0x3FFF)
    {
        /* Mirrors of PPU registers */
    }
    else if (addr >= 0x4000 && addr <= 0x4017)
    {
        /* APU and IO registers */
    }
    else if (addr >= 0x4018 && addr <= 0x401F)
    {
        /* Disabled APU and IO functionality */
    }
    else if (addr >= 0x4020)
    {
        return cart_read_byte(addr);
    }
}


void Mapper::ppu_write_byte(uint16_t addr, uint8_t byte)
{
    if (addr <= 0x1FFF)
    {
        cart_ppu_write_byte(addr, byte);
    }
    else if (addr >= 0x2000 && addr <= 0x3EFF)
    {
        uint8_t nametable_offset;
        if (cart.flag_vert_mirroring())
        {
            /* Nametable 2 and 4 map to VRAM 0x400-0x7FF */
            nametable_offset = (addr & 0x400) ? 0x400 : 0;
        }
        else
        {
            /* Nametable 3 and 4 map to VRAM 0x400-0x7FF */
            nametable_offset = (addr & 0x800) ? 0x400 : 0;
        }

        internal_vram.at(nametable_offset + (addr & 0x3FF)) = byte;
    }
    else if (addr >= 0x3F00 && addr <= 0x3FFF)
    {
        ppu_palette.at(addr & 0x1F) = byte;
    }
    else
    {
        throw std::range_error("PPU address out of range");
    }
}


uint8_t Mapper::ppu_read_byte(uint16_t addr)
{
    if (addr <= 0x1FFF)
    {
        return cart_ppu_read_byte(addr);
    }
    else if (addr >= 0x2000 && addr <= 0x3EFF)
    {
        uint8_t nametable_offset;
        if (cart.flag_vert_mirroring())
        {
            /* Nametable 2 and 4 map to VRAM 0x400-0x7FF */
            nametable_offset = (addr & 0x400) ? 0x400 : 0;
        }
        else
        {
            /* Nametable 3 and 4 map to VRAM 0x400-0x7FF */
            nametable_offset = (addr & 0x800) ? 0x400 : 0;
        }

        return internal_vram.at(nametable_offset + (addr & 0x3FF));
    }
    else if (addr >= 0x3F00 && addr <= 0x3FFF)
    {
        return ppu_palette.at(addr & 0x1F);
    }
    else
    {
        throw std::range_error("PPU address out of range");
    }
}
