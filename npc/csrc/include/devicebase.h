#ifndef __DEVICEBASE_H__
#define __DEVICEBASE_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace topdevice {
    typedef uint64_t paddr_t;
    typedef uint64_t word_t;
#define DEVICE_BASE 0xa0000000
#define MMIO_BASE 0xa0000000
#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)
#define KBD_ADDR        (DEVICE_BASE + 0x0000060)
#define RTC_ADDR        (DEVICE_BASE + 0x0000048)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
#define DISK_ADDR       (DEVICE_BASE + 0x0000300)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)
    struct deviceinfo_t {
        string name;
        paddr_t addr;
        word_t len; //byte
        bool isok;
    };
    class devicebase {
    private:

    public:
        deviceinfo_t deviceinfo;
        virtual ~devicebase() {};
        virtual void write(paddr_t addr, word_t data, uint32_t len) = 0;
        virtual word_t read(paddr_t addr) = 0;
        virtual void init(const char* name) = 0;
    };

};

#endif