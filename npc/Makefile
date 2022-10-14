TOP_MODULE := ysyx_041514

# src
CSRC +=  $(shell find $(abspath ./csrc) -name "*.cpp")
VSRC +=  $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv")

VERILATOR_INC_PATH := -I./vsrc \
			-I./vsrc/usr \
			-I./vsrc/lib 

# verilator flags: 
VERILATOR_FLAGS +=  --trace  --trace-fst
# VERILATOR_FLAGS +=  --trace-max-array 256
# VERILATOR_FLAGS +=  -threads 10
VERILATOR_FLAGS +=  -O3 -noassert --x-assign fast --x-initial fast -j$(nproc)
VERILATOR_FLAGS +=  -cc --exe  --build  --clk clk  
VERILATOR_FLAGS += ${VERILATOR_INC_PATH}
VERILATOR_FLAGS += --top ${TOP_MODULE} --prefix Vtop -Wno-DECLFILENAME


# gcc flags 
GCC_INC_PATH = -I$(NPC_HOME)/csrc/include  \
			   -I$(NPC_HOME)/csrc  \
			   -I$(NPC_HOME)/csrc/devices/include \
			   -I$(NPC_HOME)/csrc/ringbuff \
			   -I$(NPC_HOME)/csrc/soc-simulator \
			   -I/usr/include/SDL2 \

# llvm
LLVM_LIB = $(shell llvm-config --libs)
LLVM_FLAGS = $(filter-out -D__STDC_FORMAT_MACROS, $(shell llvm-config --cxxflags))

LLVM_FLAGS += -Ofast  -fexceptions  
#-lasan(内存检查)
 
GCC_LIB = -lreadline \
		  -ldl \
		  -lSDL2 

GCC_LIB += $(NPC_HOME)/libnemu.so

GCC_LIB += ${LLVM_LIB} -flto 


GCC_LDFLAGS := $(addprefix -LDFLAGS ,${GCC_LIB})
GCC_CFLAGS :=  $(addprefix -CFLAGS ,${GCC_INC_PATH})
GCC_CFLAGS += $(addprefix -CFLAGS ,${LLVM_FLAGS})
GCC_FLAGS := ${GCC_CFLAGS} ${GCC_LDFLAGS}

# run info:
OBJ_DIR := ./obj_dir
BIN := ${OBJ_DIR}/Vtop
IMG ?= $(NPC_HOME)/dummy-riscv64-npc.bin

com:${CSRC} ${VSRC}
	@verilator ${VERILATOR_FLAGS} ${CSRC} ${VSRC} ${GCC_FLAGS} 

all: default
	@echo "Write this Makefile by your self."

run: com
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# 运行 bin文件,传入 img 参数, difftest 文件参数
	${BIN} ${IMG} $(NPC_HOME)/libnemu.so
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."

clean:
	$(RM) ./obj_dir/*
	rm -rf $(BUILD_DIR)

include ./../Makefile
