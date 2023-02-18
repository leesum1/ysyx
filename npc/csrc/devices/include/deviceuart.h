#ifndef __Deviceuart_H_
#define __Deviceuart_H_

#include "devicebase.h"

namespace Topdevice {

    class Deviceuart :public Devicebase {
    private:

    public:
        Deviceuart(/* args */);
        virtual  ~Deviceuart();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void init(const char* name);
        void update();
    };

} // namespace d

#endif