#define SDL_malloc  malloc
#define SDL_free    free
#define SDL_realloc realloc

#define SDL_STBIMAGE_IMPLEMENTATION
#include "SDL_stbimage.h"

SDL_Surface* IMG_Load_RW(SDL_RWops* src, int freesrc) {
  assert(src->type == RW_TYPE_MEM);
  assert(freesrc == 0);
  printf("IMG_Load_RW\n");
  return NULL;
}

SDL_Surface* IMG_Load(const char* filename) {

  FILE* fp = fopen(filename, "r+");
  assert(fp);
  // 获取文件大小
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  assert(file_size);
  //printf("filesize:%ld\n", file_size);
  // 读取全部文件
  uint8_t* file_buf = (uint8_t*)SDL_malloc(file_size);
  assert(file_buf);
  fseek(fp, 0, SEEK_SET);
  fread(file_buf, file_size, 1, fp);
  // 转换为 surface
  SDL_Surface* s_p = STBIMG_LoadFromMemory(file_buf, file_size);
  //assert(s_p);
  // 释放内存
  fclose(fp);
  SDL_free(file_buf);
  return s_p;
}

int IMG_isPNG(SDL_RWops* src) {
  printf("IMG_isPNG\n");
  return 0;
}

SDL_Surface* IMG_LoadJPG_RW(SDL_RWops* src) {
  return IMG_Load_RW(src, 0);
}

char* IMG_GetError() {
  return SDL_GetError();
}
