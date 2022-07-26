#include "devicevga.h"

using namespace Topdevice;


Devicevga::Devicevga(/* args */) {

}
Devicevga::~Devicevga() {

}

void Devicevga::init(const char* name) {
    deviceinfo_t t;
    t.name.append(name);
    t.addr = SERIAL_PORT;
    t.len = 4;
    t.isok = true;
    deviceinfo.push_back(t);
}
void Devicevga::write(paddr_t addr, word_t data, uint32_t len) {
    putchar(data);
}
word_t Devicevga::read(paddr_t addr) {
    return 0;
}