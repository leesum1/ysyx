#ifndef __DEVICEUART_H_
#define __DEVICEUART_H_

#include "devicebase.h"

namespace Topdevice {

    class deviceuart :public Devicebase {
    private:

    public:
        deviceuart(/* args */);
        virtual  ~deviceuart();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void init(const char* name);
        void update();
    };

} // namespace d

#endif