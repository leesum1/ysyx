#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h> 
static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;

uint32_t NDL_GetTicks() {
  static struct timeval tv;
  static uint32_t time_ms;
  gettimeofday(&tv, NULL);
  time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  return time_ms;
}

/**
 * @brief 获取键盘事件
 *
 * @param buf 事件缓存
 * @param len 缓存长度
 * @return int 1:有事件
 */
int NDL_PollEvent(char* buf, int len) {
  // 使用 open 打开设备文件

  //int fd = open("/dev/events", O_RDONLY);
  //FD_EVENTS:4
  static int fd = 4;
  // 有事件
  if (read(fd, buf, len)) {
    return 1;
  }
  // 无事件
  return 0;
}

/**
 * @brief  打开一张(*w) X (*h)的画布 如果*w和*h均为0, 则将系统全屏幕作为画布, 并将*w和*h分别设为系统屏幕的大小
 *
 * @param w
 * @param h
 */
static int ndl_w, ndl_h;
void NDL_OpenCanvas(int* w, int* h) {
  // 获取屏幕大小
  char dispinfo[32];
  int dispinfo_fd = open("/proc/dispinfo", O_RDONLY);
  read(dispinfo_fd, dispinfo, sizeof(dispinfo));

  sscanf(dispinfo, "WIDTH:%d\nHEIGHT:%d\n", &ndl_w, &ndl_h);
  screen_w = ndl_w;
  screen_h = ndl_h;
  close(dispinfo_fd);
  // 将全屏幕设置为画布
  if (*w == 0 && *h == 0) {
    *w = ndl_w;
    *h = ndl_h;
  }

  if (getenv("NWM_APP")) {
    printf("NWM_APP!\n");
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
}
#define WIDTH 400
#define HEIGHT 300
void NDL_DrawRect(uint32_t* pixels, int x, int y, int w, int h) {
  /* 按页 */
  static int first = 0;
  static int fd;
  if (!first) {
    fd = open("/dev/fb", O_RDWR);
  }
  size_t offset = ((size_t)x << 32) | y;
  size_t len = ((size_t)w << 32) | h;
  lseek(fd, offset, SEEK_SET);
  write(fd, pixels, len);
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void* buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
