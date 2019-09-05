//
// Created by D Rimron-Soutter on 2019-02-26.
//

#include <arch/zxn.h>

#include "uart.h"

unsigned long prescalar;

void uart_set_baud(unsigned long speed) {
    // Work out our real speed, based on video timing
    IO_NEXTREG_REG = REG_VIDEO_TIMING;
    prescalar = uart_clock[IO_NEXTREG_DAT] / speed;

    // Set baud at 115,200
    IO_UART_BAUD_RATE = prescalar & 0x7f;                   // lower 7 bits
    IO_UART_BAUD_RATE = ((prescalar >> 7) & 0x7f) | 0x80;   // upper 7 bits
}