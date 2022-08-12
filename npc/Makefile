TOP_MODULE := top

# 原文件
CSRC +=  $(shell find $(abspath ./csrc) -name "*.cpp")
VSRC +=  $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv")

VERILATOR_INC_PATH := -I./vsrc \
			-I./vsrc/usr \
			-I./vsrc/lib 

# verilator flags: 
VERILATOR_FLAGS +=   --cc --exe --build --trace  
VERILATOR_FLAGS += ${VERILATOR_INC_PATH}
VERILATOR_FLAGS += --top ${TOP_MODULE}


# gcc flags 
GCC_INC_PATH = -I$(NPC_HOME)/csrc/include  \
			   -I$(NPC_HOME)/csrc/devices/include \
			   -I$(NPC_HOME)/csrc/ringbuff \

# llvm
LLVM_LIB = $(shell llvm-config-13 --libs)
LLVM_FLAGS = $(filter-out -D__STDC_FORMAT_MACROS, $(shell llvm-config-13 --cxxflags))

LLVM_FLAGS += -O3
#-lasan(内存检查)
GCC_LIB = -lreadline \
		  -ldl \
		  -lnemu \
		  -lSDL2
GCC_LIB += ${LLVM_LIB}


GCC_LDFLAGS := $(addprefix -LDFLAGS ,${GCC_LIB})
GCC_CFLAGS :=  $(addprefix -CFLAGS ,${GCC_INC_PATH})
GCC_CFLAGS += $(addprefix -CFLAGS ,${LLVM_FLAGS})
GCC_FLAGS := ${GCC_CFLAGS} ${GCC_LDFLAGS}

# run info:
OBJ_DIR := ./obj_dir
BIN := ${OBJ_DIR}/V${TOP_MODULE}

com:${CSRC} ${VSRC}
	@verilator ${VERILATOR_FLAGS} ${CSRC} ${VSRC} ${GCC_FLAGS} 

all: default
	@echo "Write this Makefile by your self."

run: com
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# 运行 bin文件,传入 img 参数
	${BIN} ${IMG} 
sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."

clean:
	$(RM) ./obj_dir/*
	rm -rf $(BUILD_DIR)

include ./../Makefile
