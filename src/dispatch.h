//
// Created by D Rimron-Soutter on 2019-02-26.
//

#ifndef NEXTCOM_DISPATCH_H
#define NEXTCOM_DISPATCH_H

#include "stdlib.h"
// Support workers
void switch_ram_bank(uint8_t bank);
// Dispatchers
void dispatch(void (*fn)(), uint8_t destMMU, uint8_t sourceMMU);
void dispatchWithUint8(void (*fn)(uint8_t), uint8_t id, uint8_t destMMU, uint8_t sourceMMU);

#endif //NEXTCOM_DISPATCH_H
