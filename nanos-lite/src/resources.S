.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "/home/leesum/ysyx-workbench/navy-apps/fsimg/bin/hello"
ramdisk_end:

.section .rodata
.globl logo
logo:
.incbin "resources/logo.txt"
.byte 0
