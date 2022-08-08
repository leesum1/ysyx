#include <fs.h>
#include <stdio.h>
#include <stdint.h>

typedef size_t(*ReadFn) (void* buf, size_t offset, size_t len);
typedef size_t(*WriteFn) (const void* buf, size_t offset, size_t len);


/* ramdisk 读写函数  ramdisk.c */
extern size_t ramdisk_read(void* buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void* buf, size_t offset, size_t len);
extern void init_ramdisk();
extern size_t get_ramdisk_size();



/* device 读写函数 device.c */
extern size_t serial_write(const void* buf, size_t offset, size_t len);
extern size_t events_read(void* buf, size_t offset, size_t len);
extern size_t dispinfo_read(void* buf, size_t offset, size_t len);
extern size_t fb_write(const void* buf, size_t offset, size_t len);





typedef struct {
  char* name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;

enum { FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB, FD_EVENTS, FD_DISP_INFO, FD_NUM };

size_t invalid_read(void* buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void* buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN] = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write},
  [FD_FB] = {"/dev/fb", 0, 0, invalid_read, fb_write},
  [FD_EVENTS] = {"/dev/events", 0, 0, events_read, invalid_write},
  [FD_DISP_INFO] = {"/proc/dispinfo", 0, 0, dispinfo_read, invalid_write},
#include "files.h"
};


/**
 * @brief 按行优先存储所有像素的颜色值(32位). 每个像素是`00rrggbb`的形式
 *
 */
void init_fs() {
  /* 获取屏幕信息 没有实现 sscanf 函数,无法使用 */
  // int w, h;
  // char dispinfo[32];
  // dispinfo_read(dispinfo, 0, 32);
  // sscanf(dispinfo, "WIDTH:%d\nHEIGHT:%d\n", &w, &h);


  // 直接读取屏幕信息
  AM_GPU_CONFIG_T dispinfo = io_read(AM_GPU_CONFIG);
  Log("dispinfo_WIDTH:%d,dispinfo_HEIGHT:%d", dispinfo.width, dispinfo.height);

  // 分配显存
  size_t fb_buf_size = dispinfo.height * dispinfo.width * sizeof(uint32_t);
  //uint32_t* fb_buf = malloc(fb_buf_size);
  // assert(fb_buf);
  // 更新文件记录表

  file_table[FD_FB].size = fb_buf_size;
  file_table[FD_FB].open_offset = 0;

}

/**
 * @brief 简易文件系统 open
 *
 * @param pathname 文件名
 * @param flags 不使用
 * @param mode 不使用
 * @return int 文件描述符
 */
int fs_open(const char* pathname, int flags, int mode) {
  for (size_t i = 0; i < LENGTH(file_table); i++) {
    //找到文件
    if (!strcmp(pathname, file_table[i].name)) {
      file_table[i].open_offset = 0;
      return i;
    }
  }
  //找不到文件
  Log("找不到文件:%s", pathname);
  assert(0);
  return -1;
}
/**
 * @brief 简易文件系统 read
 *
 * @param fd 文件描述符
 * @param buf
 * @param len
 * @return size_t 已读取的大小
 */
size_t fs_read(int fd, void* buf, size_t len) {
  size_t disk_offset = file_table[fd].disk_offset;
  size_t file_size = file_table[fd].size;
  size_t open_offset = file_table[fd].open_offset;

  // devices
  if (fd < FD_NUM) {
    return file_table[fd].read(buf, 0, len);
  }
  // ramdisk
  else {

    size_t read_len = len;
    // 若读取的数超出文件大小,读取到文件尾为止,此时 read_len < len
    if ((open_offset + len) > file_size) {
      // 读取剩余大小
      read_len = file_size - open_offset + 1;
    }

    ramdisk_read(buf, disk_offset + open_offset, read_len);
    file_table[fd].open_offset += read_len;
    return read_len;
  }
  return -1;
}
/**
 * @brief 简易文件系统 write
 *
 * @param fd 文件描述符
 * @param buf
 * @param len
 * @return size_t 已写入大小
 */
size_t fs_write(int fd, const void* buf, size_t len) {
  size_t disk_offset = file_table[fd].disk_offset;
  size_t file_size = file_table[fd].size;
  size_t open_offset = file_table[fd].open_offset;
  // serial, device type:char
  if (fd < FD_NUM) {
    return file_table[fd].write(buf, open_offset, len);
  }
  // ramdisk, device type:block
  else if (NULL == file_table[fd].write) {
    //不允许新增文件大小
    assert((open_offset + len) <= file_size);
    file_table[fd].open_offset += len;
    return ramdisk_write(buf, disk_offset + open_offset, len);
  }

  return -1;
}

/**
 * @brief 修改读写指针偏移
 * https://blog.csdn.net/u012349696/article/details/50083881
 * @param fd
 * @param offset
 * @param whence
 * @return size_t 新的读写指针位置
 */
size_t fs_lseek(int fd, size_t offset, int whence) {

  switch (whence) {
  case SEEK_SET:
    file_table[fd].open_offset = offset;
    break;
  case SEEK_CUR:
    file_table[fd].open_offset += offset;
    break;
  case SEEK_END:
    file_table[fd].open_offset = offset + file_table[fd].size;
    break;
  default:
    assert(0);
    break;
  }

  return file_table[fd].open_offset;
}
/**
 * @brief
 *
 * @param fd
 * @return int
 */
int fs_close(int fd) {
  //总是关闭成功
  return 0;
}
