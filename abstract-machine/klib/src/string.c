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
  *dst_p = '\0'; // 添加结束标志
  return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {

  char* dst_p = dst;
  for (size_t i = 0; i < n; i++) {
    *dst_p++ = *src++;
  }
  return dst;
}


char* strcat(char* dst, const char* src) {

  char* dst_p = dst;
  while (*dst_p != '\0') { // 移动到字符串结尾
    dst_p++;
  }
  strcpy(dst_p, src);
  return dst;
}

int strcmp(const char* s1, const char* s2) {
  int ret = 0;
  char* s1_p = (char*)s1;
  char* s2_p = (char*)s2;
  while (*s1_p != '\0' && *s2_p != '\0') {
    ret = *s1_p++ - *s2_p++;
    if (ret != 0) // 不相等直接返回
      return ret;
  }
  ret = *s1_p - *s2_p; // 比较字符串结束标志 \0
  return ret;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  int ret = 0;
  char* s1_p = (char*)s1;
  char* s2_p = (char*)s2;
  for (int i = 0; i < n;i++) {
    ret = *(s1_p++) - *(s2_p++);
    if (ret != 0)
      break;
  }
  return ret;
}

void* memset(void* s, int c, size_t n) {
  char* s_p = (char*)s;
  for (size_t i = 0;i < n;i++) {
    *(s_p++) = c;
  }
  return s;
}

void* memmove(void* dst, const void* src, size_t n) {
  char* dst_p = (char*)dst;
  char* src_p = (char*)src;
  if (dst <= src) { // 从前往后
    for (size_t i = 0; i < n; i++) {
      *dst_p++ = *src_p++;
    }
  }
  else {// 从后往前
    dst_p += (n - 1);
    src_p += (n - 1);// 移动到最后一个元素上
    for (size_t i = 0; i < n; i++) {
      *dst_p-- = *src_p--;
    }
  }
  return dst;
}

void* memcpy(void* dst, const void* src, size_t n) {

  memmove(dst, src, n);
  return dst;
}

int memcmp(const void* s1, const void* s2, size_t n) {
  int ret = 0;
  char* s1_p = (char*)s1;
  char* s2_p = (char*)s2;
  for (int i = 0; i < n;i++) {
    ret = *(s1_p++) - *(s2_p++);// 逐个比较，不相等就退出
    if (ret != 0)
      break;
  }
  return ret;
}

#endif
