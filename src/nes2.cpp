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
    prg_pages(0), chr_pages(0), flags_six(0), flags_seven(0),
    trainer(std::make_shared<std::vector<uint8_t>>())
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


auto NES2::trainer_rom() const
{
    auto t = trainer;
    return t;
}


auto NES2::prg_rom(uint8_t page) const
{
    auto p = prg.at(page);
    return p;
}


auto NES2::chr_rom(uint8_t page) const
{
    auto c = chr.at(page);
    return c;
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

    trainer = std::make_shared<std::vector<uint8_t>>();
    if (flag_trainer())
    {
        trainer->resize(TRAINER_SIZE);
        std::copy_n(nes2_it, TRAINER_SIZE, trainer->begin());
    }

    for(int i = 0; i < prg_pages; i++)
    {
        auto prg_page = std::make_shared<std::vector<uint8_t>>();
        prg_page->resize(PRG_SIZE);
        std::copy_n(nes2_it, PRG_SIZE, prg_page->begin());
        prg.push_back(prg_page);
    }

    for(int i = 0; i < chr_pages; i++)
    {
        auto chr_page = std::make_shared<std::vector<uint8_t>>();
        chr_page->resize(CHR_SIZE);
        std::copy_n(nes2_it, CHR_SIZE, chr_page->begin());
        chr.push_back(chr_page);
    }
}
