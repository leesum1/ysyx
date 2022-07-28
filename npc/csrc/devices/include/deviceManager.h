#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__


#include <string>
#include <vector>
#include <string.h>
#include "devicebase.h"
namespace Topdevice {

    class DeviceManager {
    private:
        /* data */


    public:
        vector <Devicebase*> devicePool;
        bool atRange(paddr_t s, paddr_t e, paddr_t val);
        DeviceManager(/* args */);
        ~DeviceManager();
        Devicebase* findDevicebyaddr(paddr_t addr);
        Devicebase* findDevicebyName(const char* name);
        Devicebase* createDevice(const char* name);
        word_t read(paddr_t addr);
        void write(paddr_t addr, word_t data, uint32_t len);
        bool installDevice(const char* className, const char* deviceName);
        void DeviceManagerInit(void);
        void DeviceUpdate();
    };


};
#endif