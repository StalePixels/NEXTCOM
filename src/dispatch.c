//
// Created by D Rimron-Soutter on 2019-02-26.
//

#include <arch/zxn.h>
#include <intrinsic.h>
#include <z80.h>

#include "dispatch.h"

/*******************************************************************************
 * Support Utilities
 ******************************************************************************/
void switch_ram_bank(uint8_t bank)
{
    uint8_t page = bank << 1;

    intrinsic_di();
    z80_bpoke(__SYSVAR_BANKM, ((z80_bpeek(__SYSVAR_BANKM) & 0xF8) | (bank & 0x07)));
    ZXN_WRITE_MMU6(page);
    ZXN_WRITE_MMU7(page + 1);
    intrinsic_ei();
}

/*******************************************************************************
 * Dispatchers
 ******************************************************************************/
void dispatch(void (*fn)(), uint8_t destMMU, uint8_t sourceMMU) {
    switch_ram_bank(destMMU);
    fn();
    switch_ram_bank(sourceMMU);
}

void dispatchWithUint8(void (*fn)(uint8_t), uint8_t id, uint8_t destMMU, uint8_t sourceMMU) {
    switch_ram_bank(destMMU);
    fn(id);
    switch_ram_bank(sourceMMU);
}
