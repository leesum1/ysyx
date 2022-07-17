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
  assert(dst != NULL && src != NULL);
  char* temp = dst;
  while (*temp != '\0')
    temp++;
  while ((*temp++ = *src++) != '\0');
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  while ((*s1 != '\0') && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  int t;
  t = *s1 - *s2;
  return t;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  panic("Not implemented");
}

void* memset(void* s, int c, size_t n) {
  assert(s);
  void* temp = s;
  while (n--) {
    *(char*)s = (char)c;
    s = (char*)s + 1;
  }
  return temp;
}

void* memmove(void* dst, const void* src, size_t n) {
  panic("Not implemented");
}

void* memcpy(void* out, const void* in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void* s1, const void* s2, size_t n) {
  char* arr1 = (char*)s1;
  char* arr2 = (char*)s2;
  while (--n && *arr1 && *arr1 == *arr2) {
    arr1++;
    arr2++;
  }
  return *arr1 - *arr2;
}

#endif
