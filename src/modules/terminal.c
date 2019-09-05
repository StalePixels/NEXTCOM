//
// Created by D Rimron-Soutter on 05/09/2019.
//

#include "terminal.h"
#include "../inc/ascii.h"
#include "../hardware/tilemap.h"

struct TermState termState;
char terminal_byte;
void (*byteHandler)() = &terminalHandler;

void terminalReset() {
    termState.state = TERMDUINO_NORMAL;
    termState.style = 0x0F;
    termState.next_style = 0x0F;
    termState.parameters[0] = 0;
    termState.parameters[1] = 0;
    termState.parameters[2] = 0;
    termState.parameters[3] = 0;
    // Initial terminal state
    termState.row = 0;
    termState.col = 0;

    // Visual defaults
    termState.foreground_colour    = WHITE;
    termState.background_colour    = BLACK;

    // Serial
    termState.baud                = 115200;

    // Ensure the buffer is default blank
    termState.param_buffer[0]     = '\0';
    termState.lBuffer             = 0;
    termState.pCount              = 0;
}

void terminalHandler() {
    switch (terminal_byte) {
        case ESC:
            termState.state = TERMDUINO_ESC;
            // New ESC == New Parameter stuff
            termState.pCount = 0;
            termState.param_buffer[0] = '\0';
            termState.parameters[0] = 0;
            termState.parameters[1] = 0;
            termState.parameters[2] = 0;
            termState.parameters[3] = 0;
            byteHandler = &terminalESCHandler;
            break;
        case CR:
            termState.col = 0;
            break;
        case LF:
            termState.row++;
            break;
        default:
            termState.col++;
            if (termState.col == 80) {
                termState.col = 0;
                termState.row++;

                if (termState.row == 32) termState.row = 0;
            }

            tilemap[termState.row][termState.col].tile = terminal_byte;
        }
    }
}

void terminalESCHandler() {
    switch(terminal_byte) {
        case '?':
            termState.state = TERMDUINO_WAIT_FOR_ALPHA;
            break;
        case '7':
            // TERMDUINO_ESC: Save Cursor and Attributes NOT IMPLEMENTED");
            termState.state = TERMDUINO_NORMAL;
            break;

        case '8':
            // TERMDUINO_ESC: Restore Cursor and Attributes NOT IMPLEMENTED");

            termState.state = TERMDUINO_NORMAL;
            break;
        case '[':
            // Engage "Control Sequence Introducer"
            termState.state = TERMDUINO_CSI;
            break;
        case '=':
            // NUMLOCK off
            termState.state = TERMDUINO_NORMAL;
            break;
        case '(':
            // NUMLOCK on
            termState.state = TERMDUINO_SET_CHARSET;
            break;
        default:
            // TERMDUINO_ESC: NOT IMPLEMENTED -  Waiting for ALPHA to terminate ESC"+String(x));
            termState.state = TERMDUINO_WAIT_FOR_ALPHA;
    }
}


