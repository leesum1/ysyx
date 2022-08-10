// #include <NDL.h>
// #include <sdl-video.h>
// #include <assert.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include "fixedptc.h"

// #define MAX(x, y)     (((x) > (y)) ? (x) : (y))
// #define MIN(x, y)     (((x) < (y)) ? (x) : (y))

// #define R_MASK  0XE0
// #define G_MASK  0X1C
// #define B_MASK  0x03
// #define R8(val)  ((val&R_MASK)>>5)
// #define G8(val)  ((val&G_MASK)>>3)
// #define B8(val)  ((val&B_MASK)>>2)



// /**
//  * @brief https://blog.csdn.net/caimouse/article/details/53482775
//  *    TODO:8位改造
//  * @param src
//  * @param srcrect NULL:全部拷贝
//  * @param dst
//  * @param dstrect NULL:拷贝到 (0,0) 坐标上
//  */
// void SDL_BlitSurface(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
//   assert(dst && src);
//   assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
//   uint8_t BitsPerPixel = dst->format->BitsPerPixel;
//   //printf("SDL_BlitSurface,BitsPerPixel:%d\n", dst->format->BitsPerPixel);
//   // dst 区域选择
//   uint16_t des_x = 0;
//   uint16_t des_y = 0;
//   uint16_t des_w = dst->w;
//   uint16_t des_h = dst->h;
//   if (dstrect != NULL) {
//     des_x = dstrect->x;
//     des_y = dstrect->y;
//   }
//   // src 区域选择
//   uint16_t src_x = 0;
//   uint16_t src_y = 0;
//   uint16_t src_w = src->w;
//   uint16_t src_h = src->h;
//   if (srcrect != NULL) {
//     src_x = srcrect->x;
//     src_y = srcrect->y;
//     src_w = srcrect->w;
//     src_h = srcrect->h;
//   }

//   assert(src_w <= (des_w - des_x));
//   assert(src_h <= (des_h - des_y));
//   // 像素指针
//   uint32_t* dstbuf32 = (uint32_t*)dst->pixels;
//   uint32_t* srcbuf32 = (uint32_t*)src->pixels;
//   uint8_t* dstbuf8 = (uint8_t*)dst->pixels;
//   uint8_t* srcbuf8 = (uint8_t*)src->pixels;

//   // 偏移量 必须使用 uint32_t, uint16_t 不够
//   uint32_t src_offset = src_y * src->w + src_x;
//   uint32_t des_offset = des_y * dst->w + des_x;
//   // printf("des_x:%d,des_y:%d,des_w:%d,des_h:%d\n", des_x, des_y, des_w, des_h);
//   // printf("src_x:%d,src_y:%d,src_w:%d,src_h:%d\n", src_x, src_y, src_w, src_h);
//   // printf("src_offset:%d,des_offset:%d\n", src_offset, des_offset);
//   // printf("src_offset:%d,des_offset:%d\n", src_offset, des_offset);
//   switch (BitsPerPixel) {
//   case 8:
//     // 按行复制数据
//     for (size_t i = 0; i < src_h; i++) {
//       // 复制一行
//       for (size_t j = 0; j < src_w; j++) {
//         dstbuf8[des_offset + j] = srcbuf8[src_offset + j];
//       }
//       // 偏移量移动到下一行
//       des_offset += dst->w;
//       src_offset += src->w;
//     }
//     break;
//   case 32:
//     // 按行复制数据
//     for (size_t i = 0; i < src_h; i++) {
//       // 复制一行
//       for (size_t j = 0; j < src_w; j++) {
//         dstbuf32[des_offset + j] = srcbuf32[src_offset + j];
//       }
//       // 偏移量移动到下一行
//       des_offset += dst->w;
//       src_offset += src->w;
//     }
//     break;
//   default:
//     printf("BitsPerPixel:%d\n", BitsPerPixel);
//     assert(0);
//     break;
//   }

// }
// /**
//  * @brief 测试通过 TODO:8位改造
//  *
//  * @param dst
//  * @param dstrect
//  * @param color
//  */
// void SDL_FillRect(SDL_Surface* dst, SDL_Rect* dstrect, uint32_t color) {

//   //printf("SDL_FillRect,BitsPerPixel:%d\n", dst->format->BitsPerPixel);
//   SDL_Rect rect_temp;
//   // 边界情况处理
//   if (dstrect == NULL) {
//     rect_temp.x = 0;
//     rect_temp.y = 0;
//     rect_temp.w = dst->w;
//     rect_temp.h = dst->h;
//   }
//   else {
//     rect_temp = *dstrect;
//   }
//   uint32_t bufsize = rect_temp.h * rect_temp.w;
//   uint32_t* pixels = dst->pixels;
//   for (size_t i = 0; i < bufsize; i++) {
//     pixels[i] = color;
//   }
// }
// /**
//  * @brief 测试通过
//  *
//  * @param s
//  * @param x
//  * @param y
//  * @param w
//  * @param h
//  */
// void SDL_UpdateRect(SDL_Surface* s, int x, int y, int w, int h) {
//   //printf("SDL_UpdateRect,BitsPerPixel:%d\n", s->format->BitsPerPixel);
//   // printf("SDL_Palette:%d\n", s->format->palette->ncolors);

//   // for (size_t i = 0; i < s->format->palette->ncolors; i++) {
//   //   printf("RGB%d:0x%08x\n", i, s->format->palette->colors[i].val);
//   // }

//   if (s) {
//     // SDL_Rect rect;
//     /* Perform some checking */
//     if (w == 0)
//       w = s->w;
//     if (h == 0)
//       h = s->h;
//     if ((int)(x + w) > s->w)
//       return;
//     if ((int)(y + h) > s->h)
//       return;

//     if (s->format->BitsPerPixel == 8) {
//       uint32_t* pixel32 = malloc(w * h * sizeof(uint32_t));
//       printf("w:%d,h:%d\n", w, h);
//       for (size_t i = 0; i < w * h; i++) {
//         //printf("s->pixels[%d]:%d\n", i, s->pixels[i]);
//         SDL_Color color_temp;
//         color_temp.a = 0;
//         color_temp.r = R8(s->pixels[i]);
//         color_temp.g = G8(s->pixels[i]);
//         color_temp.b = B8(s->pixels[i]);
//         pixel32[i] = color_temp.val;
//       }
//       NDL_DrawRect(pixel32, x, y, w, h);
//       //NDL_DrawRect(s->pixels, x, y, w, h);
//       free(pixel32);
//     }
//     else {
//       NDL_DrawRect(s->pixels, x, y, w, h);
//     }
//   }
// }

// // APIs below are already implemented.

// static inline int maskToShift(uint32_t mask) {
//   switch (mask) {
//   case 0x000000ff: return 0;
//   case 0x0000ff00: return 8;
//   case 0x00ff0000: return 16;
//   case 0xff000000: return 24;
//   case 0x00000000: return 24; // hack
//   default: assert(0);
//   }
// }

// SDL_Surface* SDL_CreateRGBSurface(uint32_t flags, int width, int height, int depth,
//   uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
//   assert(depth == 8 || depth == 32);
//   SDL_Surface* s = malloc(sizeof(SDL_Surface));
//   assert(s);
//   s->flags = flags;
//   s->format = malloc(sizeof(SDL_PixelFormat));
//   assert(s->format);
//   if (depth == 8) {
//     s->format->palette = malloc(sizeof(SDL_Palette));
//     assert(s->format->palette);
//     s->format->palette->colors = malloc(sizeof(SDL_Color) * 256);
//     assert(s->format->palette->colors);
//     memset(s->format->palette->colors, 0, sizeof(SDL_Color) * 256);
//     s->format->palette->ncolors = 256;
//   }
//   else {
//     s->format->palette = NULL;
//     s->format->Rmask = Rmask; s->format->Rshift = maskToShift(Rmask); s->format->Rloss = 0;
//     s->format->Gmask = Gmask; s->format->Gshift = maskToShift(Gmask); s->format->Gloss = 0;
//     s->format->Bmask = Bmask; s->format->Bshift = maskToShift(Bmask); s->format->Bloss = 0;
//     s->format->Amask = Amask; s->format->Ashift = maskToShift(Amask); s->format->Aloss = 0;
//   }

//   s->format->BitsPerPixel = depth;
//   s->format->BytesPerPixel = depth / 8;

//   s->w = width;
//   s->h = height;
//   s->pitch = width * depth / 8;
//   assert(s->pitch == width * s->format->BytesPerPixel);

//   if (!(flags & SDL_PREALLOC)) {
//     s->pixels = malloc(s->pitch * height);
//     assert(s->pixels);
//   }

//   return s;
// }

// SDL_Surface* SDL_CreateRGBSurfaceFrom(void* pixels, int width, int height, int depth,
//   int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
//   SDL_Surface* s = SDL_CreateRGBSurface(SDL_PREALLOC, width, height, depth,
//     Rmask, Gmask, Bmask, Amask);
//   assert(pitch == s->pitch);
//   s->pixels = pixels;
//   return s;
// }

// void SDL_FreeSurface(SDL_Surface* s) {
//   if (s != NULL) {
//     if (s->format != NULL) {
//       if (s->format->palette != NULL) {
//         if (s->format->palette->colors != NULL) free(s->format->palette->colors);
//         free(s->format->palette);
//       }
//       free(s->format);
//     }
//     if (s->pixels != NULL && !(s->flags & SDL_PREALLOC)) free(s->pixels);
//     free(s);
//   }
// }

// SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, uint32_t flags) {
//   if (flags & SDL_HWSURFACE) NDL_OpenCanvas(&width, &height);
//   return SDL_CreateRGBSurface(flags, width, height, bpp,
//     DEFAULT_RMASK, DEFAULT_GMASK, DEFAULT_BMASK, DEFAULT_AMASK);
// }

// void SDL_SoftStretch(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
//   assert(src && dst);
//   assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
//   assert(dst->format->BitsPerPixel == 8);

//   int x = (srcrect == NULL ? 0 : srcrect->x);
//   int y = (srcrect == NULL ? 0 : srcrect->y);
//   int w = (srcrect == NULL ? src->w : srcrect->w);
//   int h = (srcrect == NULL ? src->h : srcrect->h);

//   assert(dstrect);
//   if (w == dstrect->w && h == dstrect->h) {
//     /* The source rectangle and the destination rectangle
//      * are of the same size. If that is the case, there
//      * is no need to stretch, just copy. */
//     SDL_Rect rect;
//     rect.x = x;
//     rect.y = y;
//     rect.w = w;
//     rect.h = h;
//     SDL_BlitSurface(src, &rect, dst, dstrect);
//   }
//   else {
//     // TODO:没有测试
//     //printf("src_w:%d,src_h:%d,dst_w:%d,dst_h:%d\n", w, h, dstrect->w, dstrect->h);
//     fixedpt Stretch_w = fixedpt_div(fixedpt_fromint(dstrect->w), fixedpt_fromint(w));
//     fixedpt Stretch_h = fixedpt_div(fixedpt_fromint(dstrect->h), fixedpt_fromint(h));
//     assert(Stretch_w = Stretch_h);
//     int temp_w = fixedpt_toint(Stretch_w);
//     for (size_t i = 0; i < h; i++) {
//       for (size_t j = 0; j < w; j++) {
//         for (size_t k = 0; k < temp_w; k++) {
//           dst->pixels[(i * w + j) * temp_w + k] = src->pixels[i * w];
//         }
//       }
//     }

//     //assert(0);
//   }
// }

// void SDL_SetPalette(SDL_Surface* s, int flags, SDL_Color* colors, int firstcolor, int ncolors) {
//   assert(s);
//   assert(s->format);
//   assert(s->format->palette);
//   assert(firstcolor == 0);

//   s->format->palette->ncolors = ncolors;
//   memcpy(s->format->palette->colors, colors, sizeof(SDL_Color) * ncolors);

//   if (s->flags & SDL_HWSURFACE) {
//     assert(ncolors == 256);
//     for (int i = 0; i < ncolors; i++) {
//       uint8_t r = colors[i].r;
//       uint8_t g = colors[i].g;
//       uint8_t b = colors[i].b;
//     }
//     SDL_UpdateRect(s, 0, 0, 0, 0);
//   }
// }

// static void ConvertPixelsARGB_ABGR(void* dst, void* src, int len) {
//   int i;
//   uint8_t(*pdst)[4] = dst;
//   uint8_t(*psrc)[4] = src;
//   union {
//     uint8_t val8[4];
//     uint32_t val32;
//   } tmp;
//   int first = len & ~0xf;
//   for (i = 0; i < first; i += 16) {
// #define macro(i) \
//     tmp.val32 = *((uint32_t *)psrc[i]); \
//     *((uint32_t *)pdst[i]) = tmp.val32; \
//     pdst[i][0] = tmp.val8[2]; \
//     pdst[i][2] = tmp.val8[0];

//     macro(i + 0); macro(i + 1); macro(i + 2); macro(i + 3);
//     macro(i + 4); macro(i + 5); macro(i + 6); macro(i + 7);
//     macro(i + 8); macro(i + 9); macro(i + 10); macro(i + 11);
//     macro(i + 12); macro(i + 13); macro(i + 14); macro(i + 15);
//   }

//   for (; i < len; i++) {
//     macro(i);
//   }
// }

// SDL_Surface* SDL_ConvertSurface(SDL_Surface* src, SDL_PixelFormat* fmt, uint32_t flags) {
//   assert(src->format->BitsPerPixel == 32);
//   assert(src->w * src->format->BytesPerPixel == src->pitch);
//   assert(src->format->BitsPerPixel == fmt->BitsPerPixel);

//   SDL_Surface* ret = SDL_CreateRGBSurface(flags, src->w, src->h, fmt->BitsPerPixel,
//     fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

//   assert(fmt->Gmask == src->format->Gmask);
//   assert(fmt->Amask == 0 || src->format->Amask == 0 || (fmt->Amask == src->format->Amask));
//   ConvertPixelsARGB_ABGR(ret->pixels, src->pixels, src->w * src->h);

//   return ret;
// }

// uint32_t SDL_MapRGBA(SDL_PixelFormat* fmt, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
//   assert(fmt->BytesPerPixel == 4);
//   uint32_t p = (r << fmt->Rshift) | (g << fmt->Gshift) | (b << fmt->Bshift);
//   if (fmt->Amask) p |= (a << fmt->Ashift);
//   return p;
// }

// // pal
// int SDL_LockSurface(SDL_Surface* s) {
//   return 0;
// }
// // pal
// void SDL_UnlockSurface(SDL_Surface* s) {
// }


#include <NDL.h>
#include <sdl-video.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>


void SDL_BlitSurface(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
  //assert(0);
  assert(dst && src);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
  int dst_x, dst_y, dst_w = dst->w, dst_h = dst->h;
  int src_x, src_y, src_w = src->w, src_h = src->h;
  if (srcrect == NULL) {
    src_x = src_y = 0;
    src_w = src->w;
    src_h = src->h;
  }
  else {
    src_x = srcrect->x;
    src_y = srcrect->y;
    src_w = srcrect->w;
    src_h = srcrect->h;
  }
  if (dstrect == NULL) {
    dst_x = dst_y = 0;
    dst_w = dst->w;
    dst_h = dst->h;
  }
  else {
    dst_x = dstrect->x;
    dst_y = dstrect->y;
    dst_w = dstrect->w;
    dst_h = dstrect->h;
  }
  uint8_t* dst_color = dst->pixels, * src_color = src->pixels;
  uint32_t color_width = dst->format->palette ? 1 : 4;
  //printf("color width %d\n",color_width);
  for (int i = 0;i < src_h;i++)
    memcpy(dst_color + color_width * ((i + dst_y) * dst->w + dst_x), src_color + color_width * ((i + src_y) * src->w + src_x), color_width * src_w);
  //memcpy(dst_color+4*(i+dst_y)*dst->w+4*dst_x,src_color+4*(i+src_y)*src->w+4*src_x,4*src_w);
//SDL_UpdateRect(dst,dst_x,dst_y,dst_w,dst_h);
/* for(int i = 0; i < h;i++)
  //memcpy(dst_color+dst_w*(y+i)+x,src_color+i*w,4*w);
  for(int j = 0;j < w;j ++)
  {
    dst_color[dst_w*(y+i)+x+j] = src_color[i*w+j];
  } */

  //printf("please implement me\n");
  //assert(0);
}

void SDL_FillRect(SDL_Surface* dst, SDL_Rect* dstrect, uint32_t color) {
  //assert(0);
  assert(dst);
  int x, y, w, h;
  if (dstrect == NULL) {
    x = y = 0;
    w = dst->w;
    h = dst->h;
  }
  else {
    x = dstrect->x, y = dstrect->y, w = dstrect->w, h = dstrect->h;
  }
  if (dst->format->palette == NULL) {
    /* if(dstrect == NULL)
    {
      x = y = 0;
      w = dst->w;
      h = dst->h;
    }
    else{
      x = dstrect->x,y = dstrect->y,w = dstrect->w,h = dstrect->h;
    } */
    //NDL_OpenCanvas(&w,&h);
    uint32_t s_w = dst->w;
    uint32_t* value = (uint32_t*)dst->pixels;
    for (int i = 0;i < h;i++)
      for (int j = 0;j < w;j++) {
        value[(i + y) * s_w + j + x] = color;
      }
    //NDL_DrawRect((uint32_t*)dst->pixels,x,y,w,h);
  }
  /* else{
    //assert(0);
    uint8_t r = (color>>16)&0xff;
    uint8_t g = (color>>8)&0xff;
    uint8_t b = color&0xff;
    for(int i = 0;i < dst->format->palette->ncolors;i++)
    {
      dst->format->palette->colors[i].r = r;
      dst->format->palette->colors[i].g = g;
      dst->format->palette->colors[i].b = b;
    }
    //SDL_UpdateRect(dst,x,y,w,h);
    //assert(0);
    //uint32_t * palette = malloc(sizeof(uint32_t)*s_w*s->h);
  } */

  //printf("please implement me\n");
  //assert(0);
}

void SDL_UpdateRect(SDL_Surface* s, int x, int y, int w, int h) {
  //NDL_OpenCanvas(&w,&h);
  //assert(0);

  if (s->format->palette == NULL)
    NDL_DrawRect((uint32_t*)s->pixels, x, y, w, h);//32位的颜色,直接使用NDL
  else {
    uint32_t s_h = s->h, s_w = s->w;
    if (w == 0 || w > s_w) w = s_w;
    if (h == 0 || h > s_h) h = s_h;
    uint32_t* palette = malloc(sizeof(uint32_t) * w * h);
    memset(palette, 0, sizeof(palette));
    for (int i = 0;i < h;i++)
      for (int j = 0;j < w;j++) {
        uint8_t r = s->format->palette->colors[s->pixels[(i + y) * s_w + j + x]].r;
        uint8_t g = s->format->palette->colors[s->pixels[(i + y) * s_w + j + x]].g;
        uint8_t b = s->format->palette->colors[s->pixels[(i + y) * s_w + j + x]].b;
        palette[i * w + j] = ((r << 16) | (g << 8) | b);
      }
    NDL_DrawRect(palette, x, y, w, h);
    free(palette);
    /* printf("%d %d %d %d\n",x,y,w,h);
    for(int i = 0;i < w;i++)
      printf("%x\n",palette[i]); */
      //printf("1\n");
  }//pal8位的索引颜色
  //printf("please implement me\n");
  //assert(0);
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

void SDL_SoftStretch(SDL_Surface* src, SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) {
  assert(src && dst);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
  assert(dst->format->BitsPerPixel == 8);

  int x = (srcrect == NULL ? 0 : srcrect->x);
  int y = (srcrect == NULL ? 0 : srcrect->y);
  int w = (srcrect == NULL ? src->w : srcrect->w);
  int h = (srcrect == NULL ? src->h : srcrect->h);

  assert(dstrect);
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
  else {
    assert(0);
  }
}


void SDL_SetPalette(SDL_Surface* s, int flags, SDL_Color* colors, int firstcolor, int ncolors) {
  assert(s);
  assert(s->format);
  assert(s->format->palette);
  assert(firstcolor == 0);

  s->format->palette->ncolors = ncolors;
  memcpy(s->format->palette->colors, colors, sizeof(SDL_Color) * ncolors);
  /* for(int i = 0;i < ncolors;i++)
      printf("%dth r = %x g = %x b = %x\n",i,colors[i].r,colors[i].g,colors[i].b); */
      //printf("%d\n",s->flags);    
  if (s->flags & SDL_HWSURFACE) {
    assert(ncolors == 256);
    /* for(int i = 0;i < ncolors;i++)
      printf("%dth r = %x g = %x b = %x\n",i,colors[i].r,colors[i].g,colors[i].b); */
      /* printf("\nnew\n");
      for(int i = 0;i < s->w;i++)
        printf("%dth  color = %x\n",i,colors[s->pixels[i]]); */
    for (int i = 0; i < ncolors; i++) {
      uint8_t r = colors[i].r;
      uint8_t g = colors[i].g;
      uint8_t b = colors[i].b;
      //printf("ith = %d r = %x g = %x b = %x\n",r,g,b);
    }
    /* for(int i = 0; i< s->w;i ++)
      printf("place %d   idx = %d color = %x\n",i,s->pixels[i],colors[s->pixels[i]]); */
    SDL_UpdateRect(s, 0, 0, 0, 0);
    //while(1);
  }
}//在这里设置调色板

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

int SDL_LockSurface(SDL_Surface* s) {
  printf("please implement me\n");
  assert(0);
  return 0;
}

void SDL_UnlockSurface(SDL_Surface* s) {
  printf("please implement me\n");
  assert(0);
}


