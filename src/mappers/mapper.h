/* mapper.h - Memory Mapper Base Class */

#ifndef MAPPER_H
#define MAPPER_H

#include <vector>
#include "../nes2.h"

#define INTERNAL_RAM_SIZE 2048


class Mapper
{
public:
    explicit Mapper(const NES2& nes2);

    void write_byte(uint16_t addr, uint8_t byte);
    uint8_t read_byte(uint16_t addr);

protected:
    const NES2& cart;

private:
    std::vector<uint8_t> internal_ram;

    virtual void cart_write_byte(uint16_t addr, uint8_t byte) = 0;
    virtual uint8_t cart_read_byte(uint16_t addr) = 0;
};

#endif
