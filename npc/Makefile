TOP_MODULE := top


CSRC +=  $(shell find $(abspath ./csrc) -name "*.cpp")
VSRC +=  $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv")
INC_PATH := -I./vsrc \
			-I./vsrc/usr \
			-I./vsrc/lib \

# 2.verilator flags:
VERILATOR_FLAGS +=  --trace --cc --exe --build 
VERILATOR_FLAGS += ${INC_PATH}
VERILATOR_FLAGS += --top ${TOP_MODULE}
GCC_LDFLAGS := -LDFLAGS -ldl

# 3.run info:
OBJ_DIR := ./obj_dir
BIN := ${OBJ_DIR}/V${TOP_MODULE}

com:${CSRC} ${VSRC}
	@verilator ${VERILATOR_FLAGS} ${CSRC} ${VSRC} ${GCC_LDFLAGS}

all: default
	@echo "Write this Makefile by your self."

run: $(BIN)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@$^

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."

clean:
	$(RM) ./obj_dir/*
	rm -rf $(BUILD_DIR)

include ./../Makefile
