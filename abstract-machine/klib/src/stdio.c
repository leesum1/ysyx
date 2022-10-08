#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int vsprintf(char* buf, const char* fmt, va_list args) {
  char* buf_p = buf;
  static char str_temp[64];
  while (*fmt != '\0') {
    if (*fmt != '%') {
      *buf_p++ = *fmt++; // 普通字符，直接复制
    }
    else {
      // 先加 1 ，跳过 %
      switch (*(++fmt)) {
      case 'c':
        char ch = va_arg(args, int);
        *buf_p++ = ch;
        break;
      case 's':
        char* str = va_arg(args, char*);
        size_t len_s = strlen(str);
        strcpy(buf_p, str);
        buf_p += len_s;
        break;
      case 'd':
        int num = va_arg(args, int);
        char* num2str = itoa(num, (char*)&str_temp, 10);
        strcpy(buf_p, num2str);
        size_t len_d = strlen(num2str);
        buf_p += len_d;
        break;
      default:
        break;
      }
      fmt++;
    }
  }
  *buf_p++ = '\0';
  return buf_p - buf;
}

int snprintf(char* out, size_t n, const char* fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char* out, size_t n, const char* fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char* buf, const char* fmt, ...) {
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);
  return i;
}

void puts(const char* str) {
  while (*str)
    putch(*str++);
}

static char printf_buf[2048];
int printf(const char* fmt, ...) {
  va_list args;
  int ret;
  va_start(args, fmt);
  ret = vsprintf(printf_buf, fmt, args);
  va_end(args);

  puts(printf_buf);

  return ret;
}


#endif
