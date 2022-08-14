#include <am.h>
#include <stdlib.h>
void __am_gpu_init();
void __am_input_keybrd(AM_INPUT_KEYBRD_T*);
void __am_timer_rtc(AM_TIMER_RTC_T*);
void __am_timer_uptime(AM_TIMER_UPTIME_T*);
void __am_gpu_config(AM_GPU_CONFIG_T*);
void __am_gpu_status(AM_GPU_STATUS_T*);
void __am_gpu_fbdraw(AM_GPU_FBDRAW_T*);


static void __am_timer_config(AM_TIMER_CONFIG_T* cfg) { cfg->present = true; cfg->has_rtc = true; }
static void __am_input_config(AM_INPUT_CONFIG_T* cfg) { cfg->present = true; }
static void __am_uart_config(AM_UART_CONFIG_T* cfg) { cfg->present = false; }
// static void __am_net_config(AM_NET_CONFIG_T* cfg) { cfg->present = false; }

bool ioe_init() {
  __am_gpu_init();
  // #define PMEM_SIZE (128 * 1024 * 1024) in trm.cpp
  // 初始化 am 堆区
  heap.start = malloc(64 * 1024 * 1024);
  heap.end = heap.start + 64 * 1024 * 1024 - 1;

  return true;
}

typedef void (*handler_t)(void* buf);
static void* lut[128] = {
  [AM_TIMER_CONFIG] = __am_timer_config,
  [AM_TIMER_RTC] = __am_timer_rtc,
  [AM_TIMER_UPTIME] = __am_timer_uptime,
  [AM_INPUT_CONFIG] = __am_input_config,
  [AM_INPUT_KEYBRD] = __am_input_keybrd,
  [AM_GPU_CONFIG] = __am_gpu_config,
  [AM_GPU_FBDRAW] = __am_gpu_fbdraw,
  [AM_GPU_STATUS] = __am_gpu_status,
  [AM_UART_CONFIG] = __am_uart_config,
};

void ioe_read(int reg, void* buf) { ((handler_t)lut[reg])(buf); }
void ioe_write(int reg, void* buf) { ((handler_t)lut[reg])(buf); }
