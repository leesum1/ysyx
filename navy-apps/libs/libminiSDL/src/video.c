#include <NDL.h>
#include <sdl-video.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fixedptc.h"



/**
 * @brief https://blog.csdn.net/caimouse/article/details/53482775
 *
 * @param src
 * @param srcrect NULL:全部拷贝
 * @param dst
 * @param dstrect NULL:拷贝到 (0,0) 坐标上
 */
void SDL_BlitSurface(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
  assert(dst && src);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
  //printf("SDL_BlitSurface,BitsPerPixel:%d\n", dst->format->BitsPerPixel);
  // dst 区域选择
  uint16_t des_x = (dstrect == NULL) ? 0 : dstrect->x;
  uint16_t des_y = (dstrect == NULL) ? 0 : dstrect->y;
  uint16_t des_w = dst->w;//未使用
  uint16_t des_h = dst->h;//未使用

  // src 区域选择
  uint16_t src_x = (srcrect == NULL) ? 0 : srcrect->x;
  uint16_t src_y = (srcrect == NULL) ? 0 : srcrect->y;
  uint16_t src_w = (srcrect == NULL) ? src->w : srcrect->w;
  uint16_t src_h = (srcrect == NULL) ? src->h : srcrect->h;

  // 不支持超出范围的拷贝
  assert(src_w <= (des_w - des_x));
  assert(src_h <= (des_h - des_y));
  // 像素指针
  uint32_t* dstbuf32 = (uint32_t*)dst->pixels;
  uint32_t* srcbuf32 = (uint32_t*)src->pixels;
  uint8_t* dstbuf8 = (uint8_t*)dst->pixels;
  uint8_t* srcbuf8 = (uint8_t*)src->pixels;

  // 偏移量 必须使用 uint32_t, uint16_t 不够
  uint32_t src_offset = src_y * src->w + src_x;
  uint32_t des_offset = des_y * dst->w + des_x;
  // printf("des_x:%d,des_y:%d,des_w:%d,des->h:%d\n", des_x, des_y, des_w, des->h);
  // printf("src_x:%d,src_y:%d,src_w:%d,src_h:%d\n", src_x, src_y, src_w, src_h);
  // printf("src_offset:%d,des_offset:%d\n", src_offset, des_offset);
  // printf("src_offset:%d,des_offset:%d\n", src_offset, des_offset);
  switch (dst->format->BitsPerPixel) {
  case 8:
    // 按行复制数据
    for (size_t i = 0; i < src_h; i++) {
      // 复制一行
      for (size_t j = 0; j < src_w; j++) {
        dstbuf8[des_offset + j] = srcbuf8[src_offset + j];
      }
      // 偏移量移动到下一行
      des_offset += dst->w;
      src_offset += src->w;
    }
    break;
  case 32:
    // 按行复制数据
    for (size_t i = 0; i < src_h; i++) {
      // 复制一行
      for (size_t j = 0; j < src_w; j++) {
        dstbuf32[des_offset + j] = srcbuf32[src_offset + j];
      }
      // 偏移量移动到下一行
      des_offset += dst->w;
      src_offset += src->w;
    }
    break;
  default:
    printf("BitsPerPixel:%d\n", dst->format->BitsPerPixel);
    assert(0);
    break;
  }
}
/**
 * @brief
 *
 * @param dst
 * @param dstrect
 * @param color
 */
void SDL_FillRect(SDL_Surface* dst, SDL_Rect* dstrect, uint32_t color) {

  printf("SDL_FillRect,BitsPerPixel:%d\n", dst->format->BitsPerPixel);
  SDL_Rect rect_temp;
  // 边界情况处理
  if (dstrect == NULL) {
    rect_temp.x = 0;
    rect_temp.y = 0;
    rect_temp.w = dst->w;
    rect_temp.h = dst->h;
  }
  else {
    rect_temp = *dstrect;
  }
  uint32_t bufsize = rect_temp.h * rect_temp.w;

  switch (dst->format->BitsPerPixel) {
  case 32: {
    uint32_t* pixels32 = (uint32_t*)(dst->pixels + (rect_temp.y * dst->w + rect_temp.x) * 4);
    for (size_t i = 0; i < bufsize; i++) {
      *(pixels32++) = (uint32_t)color;
    }
    break;
  }
  case 8: {
    uint8_t* pixels8 = (uint8_t*)(dst->pixels + (rect_temp.y * dst->w + rect_temp.x));
    for (size_t i = 0; i < bufsize; i++) {
      *(pixels8++) = (uint8_t)color;
    }
    break;
  }
  default:
    printf("BitsPerPixel:%d\n", dst->format->BitsPerPixel);
    assert(0);
    break;
  }
}
/**
 * @brief 测试通过
 * SDL_UpdateRect -- Makes sure the given area is updated on the given screen.
 * @param s
 * @param x
 * @param y
 * @param w
 * @param h
 */
void SDL_UpdateRect(SDL_Surface* s, int x, int y, int w, int h) {

  assert(s);
  if (w == 0 || w > s->w) w = s->w;
  if (h == 0 || h > s->h) h = s->h;
  if (s->format->BitsPerPixel == 8) {
    uint32_t* pixels8to32 = malloc(sizeof(uint32_t) * w * h);
    uint32_t src_offset = y * s->w + x;
    uint32_t* des_offset = pixels8to32;
    for (int i = 0;i < h;i++) {
      for (int j = 0;j < w;j++) {
        /* 转换为 NDL 色彩格式 */
        SDL_Color2 color32;
        color32.a = s->format->palette->colors[s->pixels[src_offset + j]].a;
        color32.b = s->format->palette->colors[s->pixels[src_offset + j]].b;
        color32.g = s->format->palette->colors[s->pixels[src_offset + j]].g;
        color32.r = s->format->palette->colors[s->pixels[src_offset + j]].r;
        *(des_offset++) = color32.val;
      }
      src_offset += s->w;
    }
    //printf("SDL_UpdateRect,x:%d,y:%d,w:%d,h:%d\n", x, y, w, h);
    NDL_DrawRect(pixels8to32, x, y, w, h);
    free(pixels8to32);
  }
  /*s->format->BitsPerPixel == 32*/
  else {
    NDL_DrawRect((uint32_t*)s->pixels, x, y, w, h);
  }
}

// APIs below are already implemented.

static inline int maskToShift(uint32_t mask) {
  switch (mask) {
  case 0x000000ff: return 0;
  case 0x0000ff00: return 8;
  case 0x00ff0000: return 16;
  case 0xff000000: return 24;
  case 0x00000000: return 24; // hack
  default: assert(0);
  }
}

SDL_Surface* SDL_CreateRGBSurface(uint32_t flags, int width, int height, int depth,
  uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
  assert(depth == 8 || depth == 32);
  SDL_Surface* s = malloc(sizeof(SDL_Surface));
  assert(s);
  s->flags = flags;
  s->format = malloc(sizeof(SDL_PixelFormat));
  assert(s->format);
  if (depth == 8) {
    s->format->palette = malloc(sizeof(SDL_Palette));
    assert(s->format->palette);
    s->format->palette->colors = malloc(sizeof(SDL_Color) * 256);
    assert(s->format->palette->colors);
    memset(s->format->palette->colors, 0, sizeof(SDL_Color) * 256);
    s->format->palette->ncolors = 256;
  }
  else {
    s->format->palette = NULL;
    s->format->Rmask = Rmask; s->format->Rshift = maskToShift(Rmask); s->format->Rloss = 0;
    s->format->Gmask = Gmask; s->format->Gshift = maskToShift(Gmask); s->format->Gloss = 0;
    s->format->Bmask = Bmask; s->format->Bshift = maskToShift(Bmask); s->format->Bloss = 0;
    s->format->Amask = Amask; s->format->Ashift = maskToShift(Amask); s->format->Aloss = 0;
  }

  s->format->BitsPerPixel = depth;
  s->format->BytesPerPixel = depth / 8;

  s->w = width;
  s->h = height;
  s->pitch = width * depth / 8;
  assert(s->pitch == width * s->format->BytesPerPixel);

  if (!(flags & SDL_PREALLOC)) {
    s->pixels = malloc(s->pitch * height);
    assert(s->pixels);
  }

  return s;
}

SDL_Surface* SDL_CreateRGBSurfaceFrom(void* pixels, int width, int height, int depth,
  int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
  SDL_Surface* s = SDL_CreateRGBSurface(SDL_PREALLOC, width, height, depth,
    Rmask, Gmask, Bmask, Amask);
  assert(pitch == s->pitch);
  s->pixels = pixels;
  return s;
}

void SDL_FreeSurface(SDL_Surface* s) {
  if (s != NULL) {
    if (s->format != NULL) {
      if (s->format->palette != NULL) {
        if (s->format->palette->colors != NULL) free(s->format->palette->colors);
        free(s->format->palette);
      }
      free(s->format);
    }
    if (s->pixels != NULL && !(s->flags & SDL_PREALLOC)) free(s->pixels);
    free(s);
  }
}

SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, uint32_t flags) {
  if (flags & SDL_HWSURFACE) NDL_OpenCanvas(&width, &height);
  return SDL_CreateRGBSurface(flags, width, height, bpp,
    DEFAULT_RMASK, DEFAULT_GMASK, DEFAULT_BMASK, DEFAULT_AMASK);
}
/**
 * @brief https://wiki.libsdl.org/SDL_BlitScaled
 *
 * @param src
 * @param srcrect
 * @param dst
 * @param dstrect
 */
void SDL_SoftStretch(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
  assert(src && dst);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
  assert(dst->format->BitsPerPixel == 8);

  int x = (srcrect == NULL ? 0 : srcrect->x);
  int y = (srcrect == NULL ? 0 : srcrect->y);
  int w = (srcrect == NULL ? src->w : srcrect->w);
  int h = (srcrect == NULL ? src->h : srcrect->h);

  assert(dstrect);
  /* 不需要进行图像放缩 */
  if (w == dstrect->w && h == dstrect->h) {
    /* The source rectangle and the destination rectangle
     * are of the same size. If that is the case, there
     * is no need to stretch, just copy. */
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_BlitSurface(src, &rect, dst, dstrect);
  }
  /* 需要进行图像放缩 最邻近算法 https://my.oschina.net/u/4303561/blog/3827800 */
  else {
    // /printf("src_w:%d,src_h:%d,dst_w:%d,dst_h:%d\n", w, h, dstrect->w, dstrect->h);
    // 缩放比例
    fixedpt Stretch_w = fixedpt_div(fixedpt_fromint(dstrect->w), fixedpt_fromint(w));
    fixedpt Stretch_h = fixedpt_div(fixedpt_fromint(dstrect->h), fixedpt_fromint(h));
    // 性能优化,固定缩放比例 (320,200)->(400,300)
    // fixedpt Stretch_w = fixedpt_rconst(1.25);
    // fixedpt Stretch_h = fixedpt_rconst(1.5);

    for (size_t dst_y_idx = 0; dst_y_idx < dstrect->h; dst_y_idx++) {
      // y 坐标映射关系
      fixedpt src_y_idx = fixedpt_div(fixedpt_fromint(dst_y_idx), Stretch_h);
      // 对应像素偏移,不能使用 fixedpt 中的乘法运算,会溢出
      uint32_t src_PixOffset = (fixedpt_toint(src_y_idx) + y) * src->w + x;
      uint32_t dst_PixOffset = (dst_y_idx + dstrect->y) * dst->w + dstrect->x;

      for (size_t dst_x_idx = 0; dst_x_idx < dstrect->w; dst_x_idx++) {
        // x 坐标映射关系
        fixedpt src_x_idx = fixedpt_div(fixedpt_fromint(dst_x_idx), Stretch_w);
        dst->pixels[dst_PixOffset + dst_x_idx] = src->pixels[src_PixOffset + fixedpt_toint(src_x_idx)];
      }
    }
    //assert(0);
  }
}

void SDL_SetPalette(SDL_Surface* s, int flags, SDL_Color* colors, int firstcolor, int ncolors) {
  assert(s);
  assert(s->format);
  assert(s->format->palette);
  assert(firstcolor == 0);

  s->format->palette->ncolors = ncolors;
  memcpy(s->format->palette->colors, colors, sizeof(SDL_Color) * ncolors);

  if (s->flags & SDL_HWSURFACE) {
    assert(ncolors == 256);
    for (int i = 0; i < ncolors; i++) {
      uint8_t r = colors[i].r;
      uint8_t g = colors[i].g;
      uint8_t b = colors[i].b;
    }
    SDL_UpdateRect(s, 0, 0, 0, 0);
  }
}

static void ConvertPixelsARGB_ABGR(void* dst, void* src, int len) {
  int i;
  uint8_t(*pdst)[4] = dst;
  uint8_t(*psrc)[4] = src;
  union {
    uint8_t val8[4];
    uint32_t val32;
  } tmp;
  int first = len & ~0xf;
  for (i = 0; i < first; i += 16) {
#define macro(i) \
    tmp.val32 = *((uint32_t *)psrc[i]); \
    *((uint32_t *)pdst[i]) = tmp.val32; \
    pdst[i][0] = tmp.val8[2]; \
    pdst[i][2] = tmp.val8[0];

    macro(i + 0); macro(i + 1); macro(i + 2); macro(i + 3);
    macro(i + 4); macro(i + 5); macro(i + 6); macro(i + 7);
    macro(i + 8); macro(i + 9); macro(i + 10); macro(i + 11);
    macro(i + 12); macro(i + 13); macro(i + 14); macro(i + 15);
  }

  for (; i < len; i++) {
    macro(i);
  }
}

SDL_Surface* SDL_ConvertSurface(SDL_Surface* src, SDL_PixelFormat* fmt, uint32_t flags) {
  assert(src->format->BitsPerPixel == 32);
  assert(src->w * src->format->BytesPerPixel == src->pitch);
  assert(src->format->BitsPerPixel == fmt->BitsPerPixel);

  SDL_Surface* ret = SDL_CreateRGBSurface(flags, src->w, src->h, fmt->BitsPerPixel,
    fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

  assert(fmt->Gmask == src->format->Gmask);
  assert(fmt->Amask == 0 || src->format->Amask == 0 || (fmt->Amask == src->format->Amask));
  ConvertPixelsARGB_ABGR(ret->pixels, src->pixels, src->w * src->h);

  return ret;
}

uint32_t SDL_MapRGBA(SDL_PixelFormat* fmt, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  assert(fmt->BytesPerPixel == 4);
  uint32_t p = (r << fmt->Rshift) | (g << fmt->Gshift) | (b << fmt->Bshift);
  if (fmt->Amask) p |= (a << fmt->Ashift);
  return p;
}

// pal
int SDL_LockSurface(SDL_Surface* s) {
  return 0;
}
// pal
void SDL_UnlockSurface(SDL_Surface* s) {
}

