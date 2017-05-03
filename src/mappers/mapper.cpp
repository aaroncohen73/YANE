/* mapper.cpp - Memory Mapper Base Class */

#include <memory>
#include <vector>

#include "mapper.h"


Mapper::Mapper(const NES2& nes2) :
    cart(nes2)
{
    internal_ram.resize(INTERNAL_RAM_SIZE);
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
