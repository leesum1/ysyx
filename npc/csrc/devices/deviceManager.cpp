#include "deviceManager.h"
#include "deviceuart.h"
#include "devicetimer.h"
#include "assert.h"
#include "simtop.h"

using namespace Topdevice;

extern Simtop* mysim_p;
DeviceManager::DeviceManager(/* args */) {
    DeviceManagerInit();
    cout << "设备框架初始化" << endl;
}
DeviceManager::~DeviceManager() {
}
/**
 * @brief 注册所有设备
 *
 */
void DeviceManager::DeviceManagerInit(void) {
    bool ret;
    ret = installDevice("deviceuart", "uart0");
    assert(ret == true);
    printf("uart0 init\n");
    ret = installDevice("Devicetimer", "timer0");
    assert(ret == true);
    printf("timer0 init\n");
}

/**
 * @brief 是否在地址区间内
 *
 * @param s 开始地址
 * @param e 结束地址
 * @param val 查找地址
 * @return true
 * @return false
 */
bool DeviceManager::atRange(paddr_t s, paddr_t e, paddr_t val) {
    if ((s <= val) && (val <= e)) {
        return true;
    }
    return false;
}

/**
 * @brief 通过地址区间找到所属的设备
 *
 * @param addr
 * @return Devicebase*
 */
Devicebase* DeviceManager::findDevicebyaddr(paddr_t addr) {
    paddr_t staraddr, endaddr;
    /* 遍历设备池,必须使用引用遍历 */
    for (auto& iter : devicePool) {
        /* 每个设备可能有多块地址区域,例如 vga */
        for (auto dinfoiter : iter->deviceinfo) {
            if (!dinfoiter.isok) {
                continue;
            }
            staraddr = dinfoiter.addr; //地址空间开始地址
            endaddr = staraddr + dinfoiter.len - 1;//结束地址
            if (atRange(staraddr, endaddr, addr)) {
                mysim_p->u_difftest.difftest_skip_ref(); // 访问外设时,跳过 difftest
                return iter;
            }
        }
    }
    return nullptr;
}


#define DEVICE_CLASS_MATCH(className)\
do{\
    if (strcmp(name, #className) == 0)\
    {\
        return new Topdevice::className;\
    }\
}while(0)
/**
 * @brief 创造设备
 *
 * @param name 设备类名称
 * @return Devicebase* 指向设备的指针
 */
Devicebase* DeviceManager::createDevice(const char* name) {
    DEVICE_CLASS_MATCH(deviceuart);
    DEVICE_CLASS_MATCH(Devicetimer);
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
bool DeviceManager::installDevice(const char* className, const char* deviceName) {
    if (findDevicebyName(deviceName) != nullptr) {
        printf("%s,already installed\n");
        return false;
    };
    Devicebase* base = createDevice(className);
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
 * @brief 根据设备名字找设备
 *
 * @param name
 * @return Devicebase*
 */
Devicebase* DeviceManager::findDevicebyName(const char* name) {
    // for (auto iter : devicePool) {
    //     if (iter->deviceinfo.name == name) {
    //         return iter;
    //     }
    // }
    return nullptr;
}

/**
 * @brief npc 设备框架提供的统一 read 接口
 *
 * @param addr 设备地址
 * @return word_t
 */
word_t DeviceManager::read(paddr_t addr) {
    Devicebase* base = findDevicebyaddr(addr);
    if (base == nullptr) {
        cout << hex << addr << " is out of device addr" << endl;
        assert(base);
        return 0;
    }
    // 多态的用法
    word_t data = base->read(addr);
    return data;
}
/**
 * @brief npc 设备框架提供的统一 write 接口
 *
 * @param addr 设备地址
 * @param data 写入的数据
 * @param len  数据长度
 */
void DeviceManager::write(paddr_t addr, word_t data, uint32_t len) {
    assert(len >= 1 && len <= 8);
    Devicebase* base = findDevicebyaddr(addr);
    if (base == nullptr) {
        cout << hex << addr << " is out of device addr" << endl;
        assert(base);
        return;
    }
    // 多态的用法
    base->write(addr, data, len);
}