//
// Created by D Rimron-Soutter on 2019-02-26.
//

#ifndef NEXTCOM_ULA_H
#define NEXTCOM_ULA_H

#define PRINT_INK(k)                printf("\x10%c", '0'+k)
#define PRINT_PAPER(k)              printf("\x11%c", '0'+k)
#define PRINT_BRIGHT(k)             printf("\x13%d", k);
#define GOTO_XY(col, row)           printf("\x16%c%c", (col)+1, (row)+1)
#define GOTO_XY_STR(row, col, ...)  printf("\x16%c%c%s", (col)+1, (row)+1, __VA_ARGS__)

#endif //NEXTCOM_ULA_H
