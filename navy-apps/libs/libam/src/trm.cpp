#include <am.h>
#include <klib-macros.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/* am 使用的堆区, malloc 需要用到  */
Area heap;

void putch(char ch) {
    putchar(ch);
}

void halt(int code) {
    exit(code);
}
