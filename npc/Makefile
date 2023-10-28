TOP_MODULE := ysyx_22041514

# src
CSRC +=  $(shell find $(abspath ./csrc) -name "*.cpp")
VSRC +=  $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv")

# 控制参数
WAVE ?= 0
AUTO ?= 1
VGA ?= 0



VERILATOR_INC_PATH := -I./vsrc \
			-I./vsrc/usr \
			-I./vsrc/lib 

# verilator flags:
ifeq ($(WAVE),1) 
VERILATOR_FLAGS +=    --trace-fst
VERILATOR_FLAGS +=  --trace-max-array 256
endif
# VERILATOR_FLAGS +=  -threads 10
VERILATOR_FLAGS +=  -O3 -noassert --x-assign fast --x-initial fast -j $(shell nproc)
VERILATOR_FLAGS +=  -cc --exe  --build  --clk clk  
VERILATOR_FLAGS += ${VERILATOR_INC_PATH}
VERILATOR_FLAGS += --top ${TOP_MODULE} --prefix Vtop 


# gcc flags 
GCC_INC_PATH = -I$(NPC_HOME)/csrc/include  \
			   -I$(NPC_HOME)/csrc  \
			   -I$(NPC_HOME)/csrc/devices/include \
			   -I$(NPC_HOME)/csrc/ringbuff \
			   -I$(NPC_HOME)/csrc/soc-simulator \
			   -I/usr/include/SDL2 \

# llvm
LLVM_LIB = $(shell llvm-config-14 --libs)
LLVM_FLAGS = $(filter-out -D__STDC_FORMAT_MACROS, $(shell llvm-config-14 --cxxflags))

LLVM_FLAGS += -Ofast  -fexceptions  
#-lasan(内存检查)
 
GCC_LIB = -lreadline \
		  -ldl \
		  -lSDL2 

GCC_LIB += $(NPC_HOME)/libnemu.so

GCC_LIB += ${LLVM_LIB}  


GCC_LDFLAGS := $(addprefix -LDFLAGS ,${GCC_LIB})
GCC_CFLAGS :=  $(addprefix -CFLAGS ,${GCC_INC_PATH})
GCC_CFLAGS += $(addprefix -CFLAGS ,${LLVM_FLAGS})
ifeq ($(WAVE),1)
GCC_CFLAGS += $(addprefix -CFLAGS ,-DTOP_WAVE)
endif
ifeq ($(AUTO),1)
GCC_CFLAGS += $(addprefix -CFLAGS ,-DAUTO_RUN)
endif
ifeq ($(VGA),1)
GCC_CFLAGS += $(addprefix -CFLAGS ,-DDEVICE_VGA)
endif
GCC_FLAGS := ${GCC_CFLAGS} ${GCC_LDFLAGS}

# run info:
OBJ_DIR := ./obj_dir
BIN := ${OBJ_DIR}/Vtop
# IMG ?= $(NPC_HOME)/dummy-riscv64-npc.bin
IMG ?= $(NPC_HOME)/rtthread.bin
com:${CSRC} ${VSRC}

	@verilator ${VERILATOR_FLAGS} ${CSRC} ${VSRC} ${GCC_FLAGS} 


run: com
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# 运行 bin文件,传入 img 参数, difftest 文件参数
	${BIN} ${IMG} $(NPC_HOME)/libnemu.so

test:
	${BIN} ${IMG} $(NPC_HOME)/libnemu.so

clean:
	$(RM) ./obj_dir/*
	rm -rf $(BUILD_DIR)

include ./../Makefile
