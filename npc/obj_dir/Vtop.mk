# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f Vtop.mk

default: Vtop

### Constants...
# Perl executable (from $PERL)
PERL = perl
# Path to Verilator kit (from $VERILATOR_ROOT)
VERILATOR_ROOT = /usr/local/share/verilator
# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?= 
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?= 

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = Vtop
# Module prefix (from --prefix)
VM_MODPREFIX = Vtop
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
	-I/csrc/include \
	-I/csrc/devices/include \
	-I/csrc/ringbuff \
	-I/usr/lib/llvm-13/include \
	-std=c++14 \
	-fno-exceptions \
	-D_GNU_SOURCE \
	-D__STDC_CONSTANT_MACROS \
	-D__STDC_LIMIT_MACROS \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \
	-lreadline \
	-ldl \
	-lnemu \
	-lSDL2 \
	-lLLVM-13 \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
	Console \
	deviceManager \
	devicebase \
	devicekb \
	devicetimer \
	deviceuart \
	devicevga \
	main \
	mydpic \
	difftest \
	expr \
	exprinternal \
	itrace \
	mysdb \
	watchpoint \
	simMem \
	simtop \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
	/media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc \
	/media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/cppreadline \
	/media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices \
	/media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb \


### Default rules...
# Include list of all generated classes
include Vtop_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

Console.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/cppreadline/Console.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
deviceManager.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/deviceManager.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
devicebase.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/devicebase.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
devicekb.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/devicekb.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
devicetimer.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/devicetimer.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
deviceuart.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/deviceuart.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
devicevga.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/devices/devicevga.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
main.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/main.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
mydpic.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/mydpic.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
difftest.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/difftest.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
expr.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/expr.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
exprinternal.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/exprinternal.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
itrace.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/itrace.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
mysdb.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/mysdb.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
watchpoint.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/sdb/watchpoint.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
simMem.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/simMem.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<
simtop.o: /media/leesum/E0E0923EE0921ABC/WorkHome/ysyx-workbench/npc/csrc/simtop.cpp
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<

### Link rules... (from --exe)
Vtop: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a $(VM_HIER_LIBS)
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@


# Verilated -*- Makefile -*-
