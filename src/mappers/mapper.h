/* mapper.h - Memory Mapper Base Class */

#ifndef MAPPER_H
#define MAPPER_H

#include <vector>
#include "../nes2.h"

#define INTERNAL_RAM_SIZE 2048
#define INTERNAL_VRAM_SIZE 2048
#define PPU_PALETTE_SIZE 32
#define OAM_SIZE 256


class Mapper
{
public:
    explicit Mapper(const NES2& nes2);

    void write_byte(uint16_t addr, uint8_t byte);
    uint8_t read_byte(uint16_t addr);

    virtual void ppu_write_byte(uint16_t addr, uint8_t byte);
    virtual uint8_t ppu_read_byte(uint16_t addr);

protected:
    const NES2& cart;

private:
    std::array<uint8_t, INTERNAL_RAM_SIZE> internal_ram;

    std::array<uint8_t, INTERNAL_VRAM_SIZE> internal_vram;
    std::array<uint8_t, PPU_PALETTE_SIZE> ppu_palette;
    std::array<uint8_t, OAM_SIZE> oam;

    virtual void cart_write_byte(uint16_t addr, uint8_t byte) = 0;
    virtual uint8_t cart_read_byte(uint16_t addr) = 0;

    virtual void cart_ppu_write_byte(uint16_t addr, uint8_t byte) = 0;
    virtual uint8_t cart_ppu_read_byte(uint16_t addr) = 0;
};

#endif
