#ifndef __SIMMEM_H__
#define __SIMMEM_H__

#include <iostream>
#include <fstream>
#include <sys/stat.h> // struct stat
#include <string.h>
#include "deviceManager.h"
#include "simconf.h"

using namespace std;
#define PG_ALIGN __attribute((aligned(4096)))
typedef uint64_t paddr_t;
typedef uint64_t word_t;

class SimMem {

public:
    /* 实际内存 4k对齐*/
    string imgpath = "path to imgbin";
    uint8_t pmem[MEMSIZE] PG_ALIGN = {};
private:
    bool in_pmem(paddr_t addr);
    void out_of_bound(paddr_t addr);
    word_t pmem_read(paddr_t addr, int len);
    void pmem_write(paddr_t addr, int len, word_t data);

public:
    Topdevice::DeviceManager* Device; // 统一的外设入口
    SimMem(/* args */);
    ~SimMem();
    paddr_t getMEMBASE();
    // 内存读写相关
    uint8_t* guest_to_host(paddr_t paddr);
    paddr_t host_to_guest(uint8_t* haddr);
    word_t host_read(void* addr, int len);
    void host_write(void* addr, int len, word_t data);
    word_t paddr_read(paddr_t addr, int len);
    void paddr_write(paddr_t addr, int len, word_t data);
    // 加载镜像相关
    void setImagePath(const char* img);
    bool loadImage();
    size_t getImgSize();
};


#endif