#include "deviceManager.h"
#include "assert.h"

using namespace topdevice;


deviceManager::deviceManager(/* args */) {
    deviceManagerInit();
    cout << "设备框架初始化" << endl;
}
deviceManager::~deviceManager() {
}
void deviceManager::deviceManagerInit(void) {
    bool ret;
    ret = installDevice("deviceuart", "uart0");
    assert(ret == true);
    printf("uart0 init\n");
}


bool deviceManager::atRange(paddr_t s, paddr_t e, paddr_t val) {
    if ((s <= val) && (val <= e)) {
        return true;
    }
    return false;
}


devicebase* deviceManager::findDevicebyaddr(paddr_t addr) {
    paddr_t staraddr, endaddr;
    for (size_t i = 0; i < devicePool.size(); i++) {
        if (!(devicePool[i]->deviceinfo.isok)) {
            continue;
        }
        staraddr = devicePool[i]->deviceinfo.addr;
        endaddr = staraddr + devicePool[i]->deviceinfo.len - 1;
        if (atRange(staraddr, endaddr, addr)) {
            return devicePool[i];
        }
    }
    return nullptr;
}


#define DEVICE_CLASS_MATCH(className)\
do{\
    if (strcmp(name, #className) == 0)\
    {\
        return new topdevice::className;\
    }\
}while(0)
/**
 * @brief 创造设备
 *
 * @param name 设备类名称
 * @return devicebase*
 */
devicebase* deviceManager::createDevice(const char* name) {
    DEVICE_CLASS_MATCH(deviceuart);
    return NULL;
}

/**
 * @brief 安装 device
 *
 * @param className 设备类名称
 * @param deviceName 设备名称
 * @return true
 * @return false
 */
bool deviceManager::installDevice(const char* className, const char* deviceName) {
    if (findDevicebyName(deviceName) != nullptr) {
        printf("%s,already installed\n");
        return false;
    };
    devicebase* base = createDevice(className);
    if (base == nullptr) {
        printf("device has not %s\n", className);
        return false;
    }
    if (deviceName == nullptr) {
        printf("deviceName has not set");
        deviceName = className;
    }

    base->init(deviceName);
    devicePool.push_back(base);
    return true;
}
/**
 * @brief 根据名字找设备
 *
 * @param name
 * @return devicebase*
 */
devicebase* deviceManager::findDevicebyName(const char* name) {
    for (auto iter : devicePool) {
        if (iter->deviceinfo.name == name) {
            return iter;
        }
    }
    return nullptr;
}


word_t deviceManager::read(paddr_t addr) {
    devicebase* base = findDevicebyaddr(addr);
    if (base == nullptr) {
        cout << hex << addr << " is out of device addr" << endl;
        return 0;
    }
    word_t data = base->read(addr);
    return data;
}
void deviceManager::write(paddr_t addr, word_t data, uint32_t len) {
    devicebase* base = findDevicebyaddr(addr);
    if (base == nullptr) {
        cout << hex << addr << " is out of device addr" << endl;
        return;
    }
    base->write(addr, data, len);
}