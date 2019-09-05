//
// Created by D Rimron-Soutter on 02/09/2019.
//

#include "tilemap.h"

// Convert each UDG font char to a 32-byte tile using colour
// zero for unset pixel and colour 1 for set pixel
void font2bit_to_tile(unsigned char *font, unsigned char startcode, unsigned char endcode, unsigned char offset)
{
    static unsigned char *src;
    static unsigned char *dst;
    static unsigned char byte;

    for (unsigned char i = startcode; i <= endcode; ++i)
    {
        src = &font[(i - offset) * 8];
        dst = (unsigned char *)&tiles[i];

        for (unsigned char y = 0; y != 8; ++y)
        {
            byte = *src;

            for (unsigned char x = 0; x != 4; ++x)
            {
                // each byte in a tile definition holds two pixels
                // so we look at two pixels from src at a time

                *dst = 0;          // reset pixels have colour 0 (out of 16)

                if (byte & 0x80) {
                    *dst |= 0x10;  // set pixel has colour 1 (out of 16)
                }

                if (byte & 0x40) {
                    *dst |= 0x01;  // set pixel has colour 1 (out of 16)
                }

                ++dst;             // next pair of tile pixels
                byte *= 4;         // shift over two bits of source byte
            }

            ++src;
        }
    }
}
