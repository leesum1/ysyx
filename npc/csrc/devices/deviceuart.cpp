#include "deviceuart.h"

using namespace Topdevice;


deviceuart::deviceuart(/* args */) {

}
deviceuart::~deviceuart() {

}

void deviceuart::init(const char* name) {
    deviceinfo_t t;
    t.name.append(name);
    t.addr = SERIAL_PORT;
    t.len = 4;
    t.isok = true;

    deviceinfo.push_back(t);
}
void deviceuart::write(paddr_t addr, word_t data, uint32_t len) {

    //stdout（标准输出），输出方式是行缓冲。输出的字符会先存放在缓冲区，等按下回车键时才进行实际的I/O操作。
    //stderr（标准错误），是不带缓冲的，这使得出错信息可以直接尽快地显示出来。
    // putchar(data);
    putc(data, stderr);
}
word_t deviceuart::read(paddr_t addr) {
    return 0;
}
void deviceuart::update() {

}