#ifndef __DEVICEUART_H_
#define __DEVICEUART_H_

#include "devicebase.h"

namespace topdevice {

    class deviceuart :public devicebase {
    private:

    public:
        deviceuart(/* args */);
        ~deviceuart();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void init(const char* name);
    };

} // namespace d

#endif