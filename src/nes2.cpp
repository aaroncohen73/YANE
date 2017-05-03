/* nes2.cpp - NES 2.0 File Parser */

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "nes2.h"


NES2::NES2() :
    prg_pages(0), chr_pages(0), flags_six(0), flags_seven(0)
{}


uint8_t NES2::mapper() const
{
    return (flags_seven & 0xF0) | ((flags_six & 0xF0) >> 4);
}


bool NES2::flag_four_screen() const
{
    return (flags_six & 0x08) != 0;
}


bool NES2::flag_trainer() const
{
    return (flags_six & 0x04) != 0;
}


bool NES2::flag_sram() const
{
    return (flags_six & 0x02) != 0;
}


bool NES2::flag_vert_mirroring() const
{
    return (flags_six & 0x01) != 0;
}


bool NES2::flag_pc_ten() const
{
    return (flags_seven & 0x02) != 0;
}


bool NES2::flag_vs_uni() const
{
    return (flags_seven & 0x01) != 0;
}


const std::vector<uint8_t>& NES2::prg_page(uint8_t page) const
{
    return prg.at(page);
}


const std::vector<uint8_t>& NES2::chr_page(uint8_t page) const
{
    return chr.at(page);
}


void NES2::parse(const std::string filename)
{
    std::ifstream nes2;
    nes2.open(filename, std::ifstream::in);

    if (nes2.fail())
    {
        throw std::runtime_error("Unable to open iNES file");
    }

    char magic[4];
    nes2.read(magic, 4);
    if (strncmp(magic, "NES\x1A", 4) != 0)
    {
        throw std::runtime_error("Invalid iNES header");
    }

    prg_pages = nes2.get();
    chr_pages = nes2.get();
    flags_six = nes2.get();
    flags_seven = nes2.get();

    nes2.seekg(8, std::ios_base::cur);

    std::istream_iterator<uint8_t> nes2_it(nes2);

    if (flag_trainer())
    {
        trainer_rom.resize(TRAINER_SIZE);
        std::copy_n(nes2_it, TRAINER_SIZE, trainer_rom.begin());
    }

    for(int i = 0; i < prg_pages; i++)
    {
        std::vector<uint8_t> page;
        page.resize(PRG_SIZE);
        std::copy_n(nes2_it, PRG_SIZE, page.begin());
        prg.push_back(page);
    }

    for(int i = 0; i < chr_pages; i++)
    {
        std::vector<uint8_t> page;
        page.resize(CHR_SIZE);
        std::copy_n(nes2_it, CHR_SIZE, page.begin());
        chr.push_back(page);
    }
}
