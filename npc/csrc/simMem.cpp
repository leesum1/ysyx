#include "simMem.h"


SimMem::SimMem(/* args */) {
    cout << "npc内存初始化开始" << endl;
    loadImage(imgpath);
}

SimMem::~SimMem() {
    cout << "npc内存销毁完毕" << endl;
}
uint8_t* SimMem::guest_to_host(paddr_t paddr) {
    return pmem + paddr - MEMBASE;
}

paddr_t SimMem::host_to_guest(uint8_t* haddr) {
    return haddr - pmem + MEMBASE;
}


word_t SimMem::pmem_read(paddr_t addr, int len) {
    word_t ret = host_read(guest_to_host(addr), len);
    return ret;
}

void SimMem::pmem_write(paddr_t addr, int len, word_t data) {
    printf("pmem_write:%d\n", len);
    host_write(guest_to_host(addr), len, data);
}

word_t SimMem::host_read(void* addr, int len) {
    printf("host_read:%d\n", len);
    switch (len) {
    case 1:
        return *(uint8_t*)addr;
    case 2:
        return *(uint16_t*)addr;
    case 4:
        return *(uint32_t*)addr;
    case 8:
        return *(uint64_t*)addr;
    default:
        return 0;
    }
}
void SimMem::host_write(void* addr, int len, word_t data) {

    printf("host_write:%d\n", len);
    switch (len) {
    case 1:
        *(uint8_t*)addr = data;
        return;
    case 2:
        *(uint16_t*)addr = data;
        return;
    case 4:
        *(uint32_t*)addr = data;
        return;
    case 8: *(uint64_t*)addr = data;
        printf("选择8成功\n");
        return;
    default:
        break;
    }
}

bool SimMem::in_pmem(paddr_t addr) {
    return (addr >= MEMBASE) && (addr - MEMSIZE < (paddr_t)MEMBASE);
}

void SimMem::out_of_bound(paddr_t addr) {
    cout << "addr:\t" << hex << addr << "not in pmem!" << endl;
}
word_t SimMem::paddr_read(paddr_t addr, int len) {
    if (in_pmem(addr)) {
        return pmem_read(addr, len);
    }
    out_of_bound(addr);
    return 0;

}
void SimMem::paddr_write(paddr_t addr, int len, word_t data) {
    if (in_pmem(addr)) {
        pmem_write(addr, len, data);
        return;
    }
    out_of_bound(addr);
}

size_t SimMem::getImgSize(const char* img) {
    if (img == NULL) {
        return -1;
    }
    // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    struct stat statbuf;
    // 提供文件名字符串，获得文件属性结构体
    stat(img, &statbuf);
    // 获取文件大小
    size_t filesize = statbuf.st_size;
    return filesize;
}


bool SimMem::loadImage(const char* img) {
    const uint32_t defimg[] = {
    0x00000297, // auipc t0,0 ,        (pc+0) 写入 t0
    0x0002b823, // sd  zero,16(t0)     (t0+16)8byte 内存清0
    0x0102b503, // ld  a0,16(t0)       a0 写 (t0+16)8byte
    0x00100073, // ebreak (used as nemu_trap)
    0xdeadbeef // some data
    };
    ifstream binaryimg;
    size_t img_size = getImgSize(img);
    binaryimg.open(img, ios::in | ios::binary);
    if (!binaryimg.is_open() | img_size == -1) {
        memcpy(pmem, defimg, sizeof(defimg));
        return false;
    }
    cout << "imgsize:" << img_size << endl;
    binaryimg.read((char*)pmem, img_size);
    return true;
}



