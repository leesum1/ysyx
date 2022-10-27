TOP_MODULE := ysyx_041514_Stack

# src
CSRC +=  $(shell find $(abspath ./) -name "*.cpp")
VSRC +=  $(shell find $(abspath ./) -name "ysyx_041514_Stack.v")

VERILATOR_INC_PATH := -I./


# verilator flags: 
VERILATOR_FLAGS +=  --trace-fst
# VERILATOR_FLAGS +=  --trace-max-array 256
# VERILATOR_FLAGS +=  -threads 10
VERILATOR_FLAGS +=  -O3 -noassert --x-assign fast --x-initial fast -j 12
VERILATOR_FLAGS +=  -cc --exe  --build  --clk clk  
VERILATOR_FLAGS += ${VERILATOR_INC_PATH}
VERILATOR_FLAGS += --top ${TOP_MODULE} --prefix Vtest -Wno-DECLFILENAME


# gcc flags 
GCC_INC_PATH =  \


GCC_LDFLAGS := $(addprefix -LDFLAGS ,${GCC_LIB})
GCC_CFLAGS :=  $(addprefix -CFLAGS ,${GCC_INC_PATH})
GCC_CFLAGS += $(addprefix -CFLAGS ,${LLVM_FLAGS})
GCC_FLAGS := ${GCC_CFLAGS} ${GCC_LDFLAGS}

# run info:
OBJ_DIR := ./obj_dir
BIN := ${OBJ_DIR}/Vtest

com:${CSRC} ${VSRC}
	@verilator ${VERILATOR_FLAGS} ${CSRC} ${VSRC} ${GCC_FLAGS} 



run: com
# 运行 bin文件,传入 img 参数, difftest 文件参数
	${BIN}

clean:
	$(RM) ./obj_dir/*
	rm -rf $(BUILD_DIR)


