#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strnlen(const char* s, size_t count) {
  const char* s_p;
  for (s_p = s; *s_p != '\0' && ((s_p - s) < count); ++s_p)
    ;
  return (s_p - s);
}

size_t strlen(const char* s) {
  char* s_p = (char*)s;
  while (*s_p != '\0') {
    s_p++;
  }
  return (s_p - s); // 返回两个指针的距离，就是 str 的长度
}

char* strcpy(char* dst, const char* src) {
  char* dst_p = dst;
  while (*src != '\0') {
    *dst_p++ = *src++;
  }
  *dst_p = '\0';
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {

  char* dst_p = dst;
  for (size_t i = 0; i < n; i++) {
    *dst_p++ = *src++;
  }
  return dst;
}


char* strcat(char* dst, const char* src) {  //test done.

  char* dst_p = dst;
  while (*dst_p != '\0') { // dst_p -> '\0'
    dst_p++;
  }
  strcpy(dst_p, src);
  return dst;
}

int strcmp(const char* s1, const char* s2) {  //test done.
  int ret = 0;
  while (*s1 != '\0' && *s2 != '\0') {
    ret = *s1++ - *s2++;
    if (ret != 0) // 不相等直接返回
      return ret;
  }
  ret = *s1 - *s2; //check for finish '\0'.
  return ret;

}

int strncmp(const char* s1, const char* s2, size_t n) {
  int ret = 0;
  for (int i = 0; i < n;i++) {
    ret = *(s1 + i) - *(s2 + i);
    if (ret != 0)
      break;
  }
  return ret;

}

void* memset(void* s, int c, size_t n) { //test done.
  unsigned char* s_p = (unsigned char*)s;
  for (size_t i = 0;i < n;i++) {
    *(s_p + i) = c;
  }
  return s;
}

void* memmove(void* dst, const void* src, size_t n) {
  // this function can be uesd for overlapping areas.
  if (dst <= src) { // 从前往后
    // ----|dst----------|src---------|----------
    char* pdst = (char*)dst;
    char* psrc = (char*)src;
    for (size_t i = 0; i < n; i++) {
      *pdst++ = *psrc++;
    }
  }
  else {// 从后往前
    // ----|src----------|dst---------|----------
    char* pdst = (char*)dst + n;
    char* psrc = (char*)src + n;
    for (size_t i = 0; i < n; i++) {
      *--pdst = *--psrc;
    }
  }
  return dst;
}

void* memcpy(void* dst, const void* src, size_t n) {

  memmove(dst, src, n);
  return dst;
}

int memcmp(const void* s1, const void* s2, size_t n) { //test done.
  int ret = 0;
  const unsigned char* s1_p = s1;
  const unsigned char* s2_p = s2;
  for (int i = 0; i < n;i++) {
    ret = *(s1_p + i) - *(s2_p + i);
    if (ret != 0)
      break;
  }
  return ret;
}

#endif
