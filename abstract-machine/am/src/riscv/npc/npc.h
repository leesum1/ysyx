#ifndef NPC_H__
#define NPC_H__

#include <klib-macros.h>

#include "riscv/riscv.h" // the macro `ISA_H` is defined in CFLAGS
// it will be expanded as "x86/x86.h", "mips/mips32.h", ...


#define npc_trap(code) asm volatile("mv a0, %0; ebreak" : :"r"(code))

# define DEVICE_BASE 0xa0000000

#define MMIO_BASE 0xa0000000

#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)
#define KBD_ADDR        (DEVICE_BASE + 0x0000060)
#define RTC_ADDR        (DEVICE_BASE + 0x0000048)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
#define DISK_ADDR       (DEVICE_BASE + 0x0000300)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)


#endif
