//
// Created by D Rimron-Soutter on 2019-02-26.
//

#include <arch/zxn.h>
#include <arch/zxn/esxdos.h>
#include "init.h"
#include "tilemap.h"

void init_hardware(){
    // Default colour scheme
    zx_border(INK_RED);

    zx_cls(INK_BLUE | PAPER_CYAN);

    // Put Z80 in 14 MHz turbo mode.
    ZXN_NEXTREGA(REG_PERIPHERAL_2, ZXN_READ_REG(REG_PERIPHERAL_2) | RP2_ENABLE_TURBO);
    ZXN_NEXTREG(REG_TURBO_MODE, RTM_14MHZ);

    // Copy the ROM to the Tilemap...
    font2bit_to_tile((void *)0x3D00, 32, 127, 32);

    // Blank the screen
    for(uint8_t y=0;y<32;y++) {
        for(uint8_t x=0;x<80;x++){
            tilemap[y][x].tile = 32+x+y;

    /*
     * (R/W) 0x6C (108) => Default Tilemap Attribute
     *  bits 7-4 = Palette Offset
     *  bit 3    = X mirror
     *  bit 2    = Y mirrorz
     *  bit 1    = Rotate
     *  bit 0    = Tilemap over ULA
     * (bit 8 of the tile number if 512 tile mode is enabled)
     */
           tilemap[y][x].flags = 0;
        }
    }
    /*
     * 0x6E (110) R/W =>  Tilemap Base Address
     *  bits 7-6 = Read back as zero, write values ignored
     *  bits 5-0 = MSB of address of the tilemap in Bank 5
     */
    ZXN_NEXTREG(0x6e, 0x6c);                                    // tilemap base address is 0x6c00
                                                                // this gives us a wordmap of 5120 bytes
                                                                // which is 80x32 tiles, one byte per char, one per attr
    /*
     * 0x6F (111) R/W => Tile Definitions Base Address
     *  bits 7-6 = Read back as zero, write values ignored
     *  bits 5-0 = MSB of address of tile definitions in Bank 5
     */
    ZXN_NEXTREG(0x6f, 0x5c);                                    // base address 0x5c00 (ASCII chars(32+) at 0x6000+)

    /*
     * 0x6B (107) R/W  => Tilemap Control
     *  bit 7    = 1 to enable the tilemap
     *  bit 6    = 0 for 40x32, 1 for 80x32
     *  bit 5    = 1 to eliminate the attribute entry in the tilemap
     *  bit 4    = palette select
     *  bits 3-2 = Reserved set to 0
     *  bit 1    = 1 to activate 512 tile mode
     *  bit 0    = 1 to force tilemap on top of ULA
     */
    ZXN_NEXTREG(0x6b, 0xC0);                                    // enable tilemap in 80x32 "word" mode (inc. attribs)
}