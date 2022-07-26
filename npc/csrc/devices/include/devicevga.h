#ifndef __DEVICEVGA_H_
#define __DEVICEVGA_H_

#include "devicebase.h"

namespace Topdevice {

    class Devicevga :public Devicebase {
    private:

    public:
        Devicevga(/* args */);
        virtual  ~Devicevga();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void init(const char* name);
    };

} // namespace d

#endif