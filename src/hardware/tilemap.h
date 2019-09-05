//
// Created by D Rimron-Soutter on 02/09/2019.
//

#ifndef NEXTCOM_TILEMAP_H
#define NEXTCOM_TILEMAP_H

///////////////////////////////
// TILEMAP
///////////////////////////////
/*
 * 0x4000 ULA SCREEN
 *
 * 0x5c00 _tiles
 *
 */
// The tilemap will be 40/80x32 with attributes so will occupy
// the topmost 5120 bytes of bank 5 at address 0x6c00.

// The tile definitions will be placed at address 0x5c00.
// However most source fonts only defines characters 32 - 127
// which is the printable part of the ascii set so we will
// only be using those tile definitions stored in addresses
// 0x6000 - 0x6bff.

// The tilemap and used portion of tile definitions then occupy
// the top 8k of bank 5 (0x6000-0x7fff) which is well out of
// the way of the standard ula screen at 0x4000.


struct __tilemap
{
    unsigned char tile;     // 0-7 = 8 bit tile number
/*
 *   NEXTREG: 0x6C (108) R/W => Default Tilemap Attribute
 *     bits 7-4 = Palette Offset
 *     bit 3    = X mirror
 *     bit 2    = Y mirror
 *     bit 1    = Rotate
 *     bit 0    = ULA over tilemap
 *                (bit 8 of the tile number if 512 tile mode is enabled)
 */
    unsigned char flags;    // tile attribute (palette offset, rotation, etc)
};

extern struct __tilemap tilemap[32][80];

struct __tiles
{
    unsigned char bmp[32];          // each tile image is 32 bytes (64px@4bpp)
};

extern struct __tiles tiles[256];  // 256 tile images in total

// Convert each UDG font char to a 32-byte tile using colour
// zero for reset pixel and colour 1 for set pixel
void font2bit_to_tile(unsigned char *font, unsigned char startcode, unsigned char endcode, unsigned char offset);

#endif //NEXTCOM_TILEMAP_H
