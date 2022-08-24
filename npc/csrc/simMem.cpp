#include <sys/time.h>
#include <time.h>
#include "simMem.h"
#include "simconf.h"



/* 默认程序 */
const uint32_t defimg[] = {
     0x00000297, // auipc t0,0 ,        (pc+0) 写入 t0
     // 0x0002b823, // sd  zero,16(t0)     (t0+16)8byte 内存清0
     // 0x0102b503, // ld  a0,16(t0)       a0 写 (t0+16)8byte
     0x00800513, //li a0,8
     0x30552073,
     0x00100513, //li a0,9
     0x30552073,
     0x00000297, // auipc t0,0 ,        (pc+0) 写入 t0
     0x00100073, // ebreak (used as nemu_trap)
     0xdeadbeef // some data
};


SimMem::SimMem(/* args */) {
    cout << COLOR_BLUE "creat SimMem,MemSize:"
        << MEMSIZE / (1024 * 1024) << "M"
        << COLOR_END << endl;

    Device = new Topdevice::DeviceManager;
}

SimMem::~SimMem() {
    cout << COLOR_BLUE "destroy SimMem,MemSize:"
        << dec << (MEMSIZE / (1024 * 1024)) << "M"
        << COLOR_END << endl;
    delete Device;
}
/**
 * @brief 地址映射
 *  将 0x8000000 映射到数组 pmem 0号地址
 * @param paddr
 * @return uint8_t*
 */
uint8_t* SimMem::guest_to_host(paddr_t paddr) {
    return pmem + paddr - MEMBASE;
}
/**
 * @brief 地址映射,与上面相反
 *
 * @param haddr
 * @return paddr_t
 */
paddr_t SimMem::host_to_guest(uint8_t* haddr) {
    return haddr - pmem + MEMBASE;
}


word_t SimMem::pmem_read(paddr_t addr, int len) {
    word_t ret = host_read(guest_to_host(addr), len);
    return ret;
}

void SimMem::pmem_write(paddr_t addr, int len, word_t data) {
    // printf("pmem_write:%d\n", len);
    host_write(guest_to_host(addr), len, data);
}

word_t SimMem::host_read(void* addr, int len) {
    // printf("host_read:%d\n", len);
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

    // printf("host_write:%d\n", len);
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
        return;
    default:
        break;
    }
}

bool SimMem::in_pmem(paddr_t addr) {
    return (addr >= MEMBASE) && (addr - MEMSIZE < (paddr_t)MEMBASE);
}

void SimMem::out_of_bound(paddr_t addr) {
    //cout << "addr:\t" << hex << addr << " not in pmem!" << endl;
}
word_t SimMem::paddr_read(paddr_t addr, int len) {
    if (in_pmem(addr)) {
        return pmem_read(addr, len);
    }
    // ioe
    return Device->read(addr);
    out_of_bound(addr);
    return 0;

}
void SimMem::paddr_write(paddr_t addr, int len, word_t data) {
    if (in_pmem(addr)) {
        pmem_write(addr, len, data);
        return;
    }
    // ioe
    Device->write(addr, data, len);
    out_of_bound(addr);
}
/**
 * @brief 获取 bin 文件大小
 *
 * @param
 * @return size_t 若文件存在返回文件大小,负责返回默认镜像大小
 */
size_t SimMem::getImgSize() {
    // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    struct stat statbuf;
    // 提供文件名字符串，获得文件属性结构体
    int ret = stat(imgpath.c_str(), &statbuf);
    // 获取文件大小
    if (0 == ret) {
        size_t filesize = statbuf.st_size;
        return filesize;
    }
    return sizeof(defimg);
}

/**
 * @brief 加载bin镜像文件,若文件不存在会加载默认程序
 *
 * @param
 * @return true
 * @return false
 */
bool SimMem::loadImage() {
    ifstream binaryimg;
    size_t img_size = getImgSize();

    cout << COLOR_BLUE
        << "imgsize:" << img_size
        << COLOR_END << endl;

    binaryimg.open(imgpath, ios::in | ios::binary);

    if (!binaryimg.is_open() || (img_size == -1)) {
        memcpy(pmem, defimg, img_size);
        cout << COLOR_BLUE
            << "can not open image:" << imgpath
            << "load default img"
            << COLOR_END << endl;
        return true;
    }
    cout << COLOR_BLUE
        << "load img:" << imgpath
        << COLOR_END << endl;
    binaryimg.read((char*)pmem, img_size);
    return true;
}


void SimMem::setImagePath(const char* img) {
    string path(img);
    imgpath.clear();
    imgpath.append(img);
    cout << COLOR_BLUE "ImgPath: "
        << imgpath
        << COLOR_END << endl;
}

paddr_t SimMem::getMEMBASE() {
    return MEMBASE;
}


