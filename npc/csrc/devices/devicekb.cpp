#include "devicekb.h"

using namespace Topdevice;


Devicekb::Devicekb(/* args */) {

}
Devicekb::~Devicekb() {

}

void Devicekb::init(const char* name) {
    deviceinfo_t t;
    t.name.append(name);
    t.addr = KBD_ADDR;
    t.len = 4;
    t.isok = true;

    deviceinfo.push_back(t);
}
void Devicekb::write(paddr_t addr, word_t data, uint32_t len) {
    putchar(data);
}
word_t Devicekb::read(paddr_t addr) {
    keybuff.push_back(2);
    return 0;
}

void Devicekb::update() {

}