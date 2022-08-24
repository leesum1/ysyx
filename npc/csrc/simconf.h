#ifndef __SIMCONF_H__
#define __SIMCONF_H__

#define FONT_BOLD "\e[1m"
#define FONT_END "\e[1m"

// 颜色加粗
#define COLOR_GREEN FONT_BOLD "\033[32m" 
#define COLOR_RED   FONT_BOLD "\033[31m"
#define COLOR_YELLOW FONT_BOLD "\033[33m"
#define COLOR_BLUE FONT_BOLD "\033[34m"
#define COLOR_END  FONT_END "\033[0m" 


#define MEMSIZE 0x8000000 //((128 * 1024 * 1024))
#define MEMBASE 0x80000000 

//#define AUTO_RUN
#define TOP_TRACE
//#define MTRACH


#endif