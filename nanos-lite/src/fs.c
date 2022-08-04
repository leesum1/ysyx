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

enum { FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB };

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
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
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


  // 若读取的数超出文件大小,读取到文件尾为止,此时 read_len < len
  size_t read_len = len;
  if ((open_offset + len) > file_size) {
    read_len = open_offset + len - file_size;
  }

  ramdisk_read(buf, disk_offset + open_offset, read_len);
  file_table[fd].open_offset += len;
  return read_len;
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
  // if (fd <= 2) {
  //   file_table->write(buf, 0, len);
  // }
  // ramdisk, device type:block
  if (NULL == file_table->write) {
    //不允许新增文件大小
    assert((open_offset + len) <= file_size);
    ramdisk_write(buf, disk_offset + open_offset, len);
    file_table[fd].open_offset += len;
  }

  return len;
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
