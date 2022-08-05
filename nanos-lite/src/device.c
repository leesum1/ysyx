#include <common.h>

#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char* keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void* buf, size_t offset, size_t len) {

  for (size_t i = 0; i < len; i++) {
    putch(*(char*)(buf + i));
  }
  return len;
}
/**
 * @brief 读取键盘事件,没有进行长度检查
 *
 * @param buf 读取缓存
 * @param offset 未使用
 * @param len 缓存长度(需要大于10)
 * @return size_t 0:无按键事件 1:有按键事件
 */
size_t events_read(void* buf, size_t offset, size_t len) {
  assert(len > 10);
  AM_INPUT_KEYBRD_T kb = io_read(AM_INPUT_KEYBRD);
  if (kb.keydown) {
    sprintf(buf, "kd %s\n", keyname[kb.keycode]);
  }
  else {
    sprintf(buf, "ku %s\n", keyname[kb.keycode]);
  }
  //Log("keybuff:%s\n", buf);
  // 无按键事件
  if (kb.keycode == 0) {
    return 0;
  }

  return 1;
}

size_t dispinfo_read(void* buf, size_t offset, size_t len) {
  assert(len > 20);
  AM_GPU_CONFIG_T dispinfo = io_read(AM_GPU_CONFIG);
  sprintf(buf, "WIDTH:%d\nHEIGHT:%d\n", dispinfo.width, dispinfo.height);
  return len;
}

size_t fb_write(const void* buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
