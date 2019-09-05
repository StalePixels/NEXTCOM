//
// Created by D Rimron-Soutter on 2019-02-26.
//

#ifndef NEXTCOM_UART_H
#define NEXTCOM_UART_H

#include <stdio.h>
#include <arch/zxn.h>

static unsigned long speeds[] = { 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115000, 230000, 460000, 920000 };
static unsigned long uart_clock[] = { CLK_28_0, CLK_28_1, CLK_28_2, CLK_28_3, CLK_28_4, CLK_28_5, CLK_28_6, CLK_28_7 };

#define printInk(k)                 printf("\x10%c", '0'+k)
#define printPaper(k)               printf("\x11%c", '0'+k)
#define printBright(k)              printf("\x13%d", k);
#define printAt(row, col)           printf("\x16%c%c", (col)+1, (row)+1)
#define printAtStr(row, col, ...)   printf("\x16%c%c%s", (col)+1, (row)+1, __VA_ARGS__)

void uart_set_baud(unsigned long speed);

#endif //NEXTCOM_UART_H
