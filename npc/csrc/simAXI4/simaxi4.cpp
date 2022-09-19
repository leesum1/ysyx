#include "simaxi4.h"
#include "simtop.h"
#include "uart8250.hpp"
#include <thread>
#include <termios.h>

// void uart_input(uart8250& uart) {
//     termios tmp;
//     tcgetattr(STDIN_FILENO, &tmp);
//     tmp.c_lflag &= (~ICANON & ~ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
//     while (running) {
//         char c = getchar();
//         // if (c == 'p') printf("pc = %x\n", *pc);
//         // else if (c == 't') trace_on = true;
//         if (c == 10) c = 13; // convert lf to cr
//         uart.putc(c);
//     }
// }


// extern Simtop* mysim_p;
SimAxi4::SimAxi4(Vtop* top) {
    cout << "2" << endl;
    assert(top);
    cout << "2" << endl;
    connect_wire(mmio_ptr, top);// 链接端口
    cout << "1" << endl;
    assert(mmio_ptr.check());
    mmio_device_init();
    cout << COLOR_BLUE "axi4 init success" COLOR_END << endl;
}

SimAxi4::~SimAxi4() {

}


void SimAxi4::connect_wire(axi4_ptr <32, 64, 4>& mmio_ptr, Vtop* top) {
    // connect
    // mmio
    // aw   
    mmio_ptr.awaddr = &(top->io_master_awaddr);
    mmio_ptr.awburst = &(top->io_master_awburst);
    mmio_ptr.awid = &(top->io_master_awid);
    mmio_ptr.awlen = &(top->io_master_awlen);
    mmio_ptr.awready = &(top->io_master_awready);
    mmio_ptr.awsize = &(top->io_master_awsize);
    mmio_ptr.awvalid = &(top->io_master_awvalid);

    // w
    mmio_ptr.wdata = &(top->io_master_wdata);
    mmio_ptr.wlast = &(top->io_master_wlast);
    mmio_ptr.wready = &(top->io_master_wready);
    mmio_ptr.wstrb = &(top->io_master_wstrb);
    mmio_ptr.wvalid = &(top->io_master_wvalid);
    // b
    mmio_ptr.bid = &(top->io_master_bid);
    mmio_ptr.bready = &(top->io_master_bready);
    mmio_ptr.bresp = &(top->io_master_bresp);
    mmio_ptr.bvalid = &(top->io_master_bvalid);
    // ar
    mmio_ptr.araddr = &(top->io_master_araddr);
    mmio_ptr.arburst = &(top->io_master_arburst);
    mmio_ptr.arid = &(top->io_master_arid);
    mmio_ptr.arlen = &(top->io_master_arlen);
    mmio_ptr.arready = &(top->io_master_arready);
    mmio_ptr.arsize = &(top->io_master_arsize);
    mmio_ptr.arvalid = &(top->io_master_arvalid);
    // r
    mmio_ptr.rdata = &(top->io_master_rdata);
    mmio_ptr.rid = &(top->io_master_rid);
    mmio_ptr.rlast = &(top->io_master_rlast);
    mmio_ptr.rready = &(top->io_master_rready);
    mmio_ptr.rresp = &(top->io_master_rresp);
    mmio_ptr.rvalid = &(top->io_master_rvalid);
}


void SimAxi4::mmio_device_init() {

    axi4     <32, 32, 4> mmio_sigs;
    axi4_ref <32, 32, 4> mmio_sigs_ref(mmio_sigs);

    // // uart8250 at 0x1fe40000 (APB)
    // uart8250 uart;
    // std::thread* uart_input_thread = new std::thread(uart_input, std::ref(uart));
    // assert(mmio.add_dev(SERIAL_PORT, 4, &uart));

    // 内存
    dram = new mmio_mem(0x8000000);
    assert(mmio.add_dev(MEM_BASE, 0x8000000, dram));
}

void SimAxi4::update_input() {
    axi4_ref <32, 64, 4> mmio_sigs_ref(mmio_sigs); // 用于 soc-simulator 的内部信号处理
    axi4_ref <32, 64, 4> mmio_ref(mmio_ptr); // 指向 npc 与 soc-simulator 的交互信号

    // posedge
    mmio_sigs.update_input(mmio_ref); // 读取 npc 的 axi 信号


}
void SimAxi4::beat() {
    axi4_ref <32, 64, 4> mmio_sigs_ref(mmio_sigs); // 用于 soc-simulator 的内部信号处理
    axi4_ref <32, 64, 4> mmio_ref(mmio_ptr); // 指向 npc 与 soc-simulator 的交互信号
    mmio.beat(mmio_sigs_ref);   // soc-simulator 根据信号做出反映

}
void SimAxi4::update_output() {
    axi4_ref <32, 64, 4> mmio_sigs_ref(mmio_sigs); // 用于 soc-simulator 的内部信号处理
    axi4_ref <32, 64, 4> mmio_ref(mmio_ptr); // 指向 npc 与 soc-simulator 的交互信号
    mmio_sigs.update_output(mmio_ref);// 返回 npc axi 信号
}
