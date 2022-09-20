#ifndef __MMIO_DEVICE2AXI4_HPP
#define __MMIO_DEVICE2AXI4_HPP


#include "axi4.hpp"
#include "mmio_dev.hpp"
#include "deviceManager.h"
#include "devicebase.h"
#include <fstream>
#include <iostream>



class Device2axi4 : public mmio_dev {
private:

    Topdevice::DeviceManager* myDevices;
    uint64_t getRealAddr(uint64_t start_addr) {

        return start_addr + MMIO_BASE;
    }

public:
    Device2axi4() {
        myDevices = new Topdevice::DeviceManager;
        cout << "Device2axi4 init" << endl;
    };
    ~Device2axi4() {
        delete myDevices;

    }
    bool do_read(uint64_t start_addr, uint64_t size, uint8_t* buffer) {
        static uint64_t rdata = 0;
        rdata = myDevices->read(getRealAddr(start_addr));
        memcpy(buffer, &rdata, size);
        return true;
    }
    bool do_write(uint64_t start_addr, uint64_t size, const uint8_t* buffer) {
        uint64_t wdata = *(uint64_t*)buffer;
        myDevices->write(getRealAddr(start_addr), wdata, size);
        return true;
    }
};

#endif