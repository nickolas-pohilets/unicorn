/*
 * Dummy board with just RAM and CPU for use as an ISS.
 *
 * Copyright (c) 2007 CodeSourcery.
 *
 * This code is licensed under the GPL
 */

/* Unicorn Emulator Engine */
/* By Nguyen Anh Quynh, 2015 */

#include "hw/hw.h"
#include "hw/m68k/m68k.h"
#include "hw/boards.h"
#include "exec/address-spaces.h"


/* Board init.  */
static int dummy_m68k_init(struct uc_struct *uc, MachineState *machine)
{
    const char *cpu_model = machine->cpu_model;
    CPUM68KState *env;

    if (!cpu_model)
        cpu_model = "cfv4e";

    env = cpu_init(uc, cpu_model);
    if (!env) {
        fprintf(stderr, "Unable to find m68k CPU definition\n");
        return -1;
    }

    /* Initialize CPU registers.  */
    env->vbr = 0;
    env->pc = 0;

    return 0;
}

void dummy_m68k_machine_init(struct uc_struct *uc)
{
    static const QEMUMachine dummy_m68k_machine = {
        NULL,            // family
        "dummy",         // name
        dummy_m68k_init, // init
        NULL,            // reset
        0,               // max_cpus
        1,               // is_default
        UC_ARCH_M68K     // arch
    };
    //printf(">>> dummy_m68k_machine_init\n");
    qemu_register_machine(uc, &dummy_m68k_machine, TYPE_MACHINE, NULL);
}
