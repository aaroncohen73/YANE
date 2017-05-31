/* mapper_0.h - iNES mapper 0 (NROM) */

#ifndef MAPPER_0_H
#define MAPPER_0_H

#include "mapper.h"


class Mapper_0 : public Mapper
{
public:
    explicit Mapper_0(const NES2& nes2);

private:
    void cart_write_byte(uint16_t addr, uint8_t byte) override;
    uint8_t cart_read_byte(uint16_t addr) override;

    void cart_ppu_write_byte(uint16_t addr, uint8_t byte) override;
    uint8_t cart_ppu_read_byte(uint16_t addr) override;
};

#endif
