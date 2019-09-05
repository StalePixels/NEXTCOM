//
// Created by D Rimron-Soutter on 2019-01-05.
//

#include <z80.h>
#include <arch/zxn.h>
#include <arch/zxn/esxdos.h>

#include <ctype.h>
#include <errno.h>
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>

#include "dispatch.h"
#include "inc/ascii.h"
#include "modules/terminal.h"
#include "hardware/init.h"
#include "hardware/uart.h"
#include "hardware/tilemap.h"

/*
 * Defines
 */

#define MACRO__WAITKEY                     while(in_inkey()==0){};while(in_inkey()!=0){};

uint8_t current_speed = 9;
uint8_t bytes_read = 0;
uint8_t border_colour = 0;
bool active = true;

int main() {
    char command_letter = '\0';
    init_hardware();
    uart_set_baud(speeds[current_speed]);
    unsigned char i;

    // fill in tilemap palette 0

    // try to fill in different colours for each 16-colour offset
    // make sure colours 0 and 1 in each 16-colour group are contrasting

    ZXN_NEXTREG(REG_PALETTE_CONTROL, 0x30);
    ZXN_NEXTREG(REG_PALETTE_INDEX, 0);

    i = 0;
    do
    {
        unsigned char value;

        value = i & 0xfe;
        if (value == 0) value = 1;

        ZXN_NEXTREGA(REG_PALETTE_VALUE_8, (i & 1) ? value : ~value);
    }
    while (++i != 0);

    terminalReset();

    do {
        // we're ready to send data now?!
        if (command_letter) {
            while (IO_UART_STATUS & IUS_TX_BUSY);  // Busy wait to send a single byte.
            // Allen Says: max wait time is less than 10 bit periods.
            IO_UART_TX = command_letter;
        }

        if (IO_UART_STATUS & IUS_RX_AVAIL) {
            if (border_colour == 8) {
                border_colour = 0;
            }
            zx_border(border_colour);

            terminal_byte = IO_UART_RX;
            byteHandler();

        }
    }
    while (active);
}