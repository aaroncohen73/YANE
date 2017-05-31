/* nes2.h - NES 2.0 File Parser */

#ifndef NES2_H
#define NES2_H

#include <array>
#include <memory>
#include <string>
#include <vector>

#define TRAINER_SIZE 512
#define PRG_SIZE 16384
#define CHR_SIZE 8192


class NES2
{
public:
    uint8_t prg_pages;  // Number of PRG (16384 byte) ROM pages
    uint8_t chr_pages;  // Number of CHR (8192 byte) ROM pages

    std::array<uint8_t, TRAINER_SIZE> trainer_rom;  // Trainer ROM

    typedef std::array<uint8_t, PRG_SIZE> prg_page;
    typedef std::array<uint8_t, CHR_SIZE> chr_page;

    NES2();

    /* The ROM's mapper number */
    uint8_t mapper() const;

    /* Four-screen mode */
    bool flag_four_screen() const;

    /* 512-byte trainer @ 7000-71FFh */
    bool flag_trainer() const;

    /* Battery-backed SRAM @ 6000-7FFFh */
    bool flag_sram() const;

    /* Horizontal/Vertical mirroring */
    bool flag_vert_mirroring() const;

    /* Playchoice 10 game */
    bool flag_pc_ten() const;

    /* Vs. Unisystem game */
    bool flag_vs_uni() const;

    /* PRG ROM page */
    const prg_page& prg_page_at(uint8_t page) const;

    /* CHR ROM page */
    const chr_page& chr_page_at(uint8_t page) const;

    /* Parse file */
    void parse(const std::string filename);

private:
    uint8_t flags_six;  // Byte 6 flags field
    uint8_t flags_seven;  // Byte 7 flags field

    std::vector<prg_page> prg;  // PRG ROM
    std::vector<chr_page> chr;  // CHR ROM
    /* No support for PRG or CHR RAM right now */
    /* No support for PC-10 games right now */
};

#endif
