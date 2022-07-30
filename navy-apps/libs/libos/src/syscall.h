#ifndef __SYSCALL_H__
#define __SYSCALL_H__

enum {
  SYS_exit,
  SYS_yield,
  SYS_open,
  SYS_read,
  SYS_write,
  SYS_kill,
  SYS_getpid,
  SYS_close,
  SYS_lseek,
  SYS_brk,
  SYS_fstat,
  SYS_time,
  SYS_signal,
  SYS_execve,
  SYS_fork,
  SYS_link,
  SYS_unlink,
  SYS_wait,
  SYS_times,
  SYS_gettimeofday
};

// void _exit(int status);
// int _open(const char* path, int flags, mode_t mode);
// int _write(int fd, void* buf, size_t count);
// void* _sbrk(intptr_t increment);
// int _read(int fd, void* buf, size_t count);
// int _close(int fd);
// off_t _lseek(int fd, off_t offset, int whence);
// int _gettimeofday(struct timeval* tv, struct timezone* tz);
// int _execve(const char* fname, char* const argv[], char* const envp[]);
// Syscalls below are not used in Nanos-lite.
// But to pass linking, they are defined as dummy functions.

#endif
