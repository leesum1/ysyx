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
    putchar(data);
}
word_t deviceuart::read(paddr_t addr) {
    return 0;
}

void deviceuart::update() {

}