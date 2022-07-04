#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

/*长度不包含'\0'*/
size_t strlen(const char* s) {
  size_t len = 0;
  while (*s != '\0') {
    len++;
    s++;
  }
  return len;
}

char* strcpy(char* dst, const char* src) {
  char* address = dst;
  int size = strlen(dst) + 1;
  if ((dst > src) && (dst <= src + size - 1)) //内存重叠，从尾往前复制
  {
    src = src + size - 1;
    dst = dst + size - 1;
    while (size--) {
      *dst-- = *src--;
    }
  }
  else//正常情况，从头往后复制
  {
    while (size--) {
      *dst++ = *src++;
    }
  }
  return address;
}

char* strncpy(char* dst, const char* src, size_t n) {
  panic("Not implemented");
}

char* strcat(char* dst, const char* src) {
  panic("Not implemented");
}

int strcmp(const char* s1, const char* s2) {
  panic("Not implemented");
}

int strncmp(const char* s1, const char* s2, size_t n) {
  panic("Not implemented");
}

void* memset(void* s, int c, size_t n) {
  panic("Not implemented");
}

void* memmove(void* dst, const void* src, size_t n) {
  panic("Not implemented");
}

void* memcpy(void* out, const void* in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void* s1, const void* s2, size_t n) {
  panic("Not implemented");
}

#endif
