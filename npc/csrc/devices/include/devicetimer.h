#ifndef __DEVICETIMER_H_
#define __DEVICETIMER_H_

#include "devicebase.h"
#include <sys/time.h>
namespace Topdevice {

    class Devicetimer :public Devicebase {
    private:
        timeval boottime;
        timeval now;
        uint64_t rtc_time;
    public:
        Devicetimer(/* args */);
        virtual  ~Devicetimer();
        void write(paddr_t addr, word_t data, uint32_t len);
        word_t read(paddr_t addr);
        void update();
        void init(const char* name);
    };

}

#endif