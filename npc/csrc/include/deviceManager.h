#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__


#include <string>
#include <vector>
#include <string.h>
#include "devicebase.h"
#include "deviceuart.h"

namespace topdevice {

    class deviceManager {
    private:
        /* data */
        vector <devicebase*> devicePool;

    public:
        bool atRange(paddr_t s, paddr_t e, paddr_t val);
        deviceManager(/* args */);
        ~deviceManager();
        devicebase* findDevicebyaddr(paddr_t addr);
        devicebase* findDevicebyName(const char* name);
        devicebase* createDevice(const char* name);
        word_t read(paddr_t addr);
        void write(paddr_t addr, word_t data, uint32_t len);
        bool installDevice(const char* className, const char* deviceName);
        void deviceManagerInit(void);
    };


};
#endif