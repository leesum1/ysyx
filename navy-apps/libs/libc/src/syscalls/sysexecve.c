/* connector for execve */

#include <reent.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int
execve(const char* name,
  char* const argv[],
  char* const env[]) {

  int ret = _execve_r(_REENT, name, argv, env);
  printf("ret:%d\n",ret);
  if (ret<0)
  {
    errno = -ret;
    return -1;
  }
  return 0;
}
