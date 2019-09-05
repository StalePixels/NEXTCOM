//
// Created by D Rimron-Soutter on 05/09/2019.
//
#include <stdlib.h>

#ifndef NEXTCOM_TERMINAL_H
#define NEXTCOM_TERMINAL_H


#define BLACK                                             0x0000
#define BLUE                                              0x001F
#define RED                                               0xF800
#define GREEN                                             0x07E0
#define CYAN                                              0x07FF
#define MAGENTA                                           0xF81F
#define YELLOW                                            0xFFE0
#define WHITE                                             0xFFFF

// Term State -- the terminal is always "waiting for one of these"
typedef enum  {
    //  In normal ASCII mode, command-interpretation starts with...
            TERMDUINO_NORMAL,           // Waiting for 'start' byte of command
    // Waiting for second byte
            TERMDUINO_ESC,              // + next ESC Sequence command, total byte 2
    // Command Types
            TERMDUINO_CSI,              // Control Sequence Introducer
    TERMDUINO_SGI,              // Select Graphic Rendition
    TERMDUINO_SET_CHARSET,      // Pick Charset/Fontface
    // Dummy mode
            TERMDUINO_WAIT_FOR_ALPHA,   // Do nothing until *AFTER* we get byte = 40<>7E
} TermStates;

/*
 * Global state of our terminal, cursor, colours, and other important information
 */
struct TermState {
    TermStates      state;              // Our ENUM, above

    unsigned char   style;              // Current active style to print next
    unsigned char   prev_byte;          // TO check for parampushing

    uint8_t         parameters[4];      //    as passed via ESC(CSI) codes

    uint8_t         row;                // Cursor Y
    uint8_t         col;                // Cursor X

    // Eventually refactor to these, not "style" -- as it allows more control with pigfx
    uint32_t        foreground_colour;
    uint32_t        background_colour;

    // Serial bits
    long            baud;
    uint8_t         portConfig;

    // Temp storage for runtime
    unsigned char   next_style;         // Building next style byte storage
    unsigned char   param_buffer[32];   //  and a buffer so we can parse the string
    uint8_t         lBuffer;            //  and the length for "next char"
    uint8_t         pCount;             // Number of parameters
};

extern char terminal_byte;

extern void (*byteHandler)();
void terminalReset();
void terminalHandler();
void terminalESCHandler();
void terminalCSIHandler();

#endif //NEXTCOM_TERMINAL_H
