#include "deviceuart.h"

using namespace topdevice;


deviceuart::deviceuart(/* args */) {

}
deviceuart::~deviceuart() {

}

void deviceuart::init(const char* name) {
    deviceinfo.name.append(name);
    deviceinfo.addr = SERIAL_PORT;
    deviceinfo.len = 4;
    deviceinfo.isok = true;
}
void deviceuart::write(paddr_t addr, word_t data, uint32_t len) {
    putchar(data);
}
word_t deviceuart::read(paddr_t addr) {
    return 0;
}