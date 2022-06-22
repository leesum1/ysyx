#需要仿真的模块名称
MODULE_NAME := lab01switch

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator -Wall --cc --exe --build ./csrc/$(MODULE_NAME).cpp ./vsrc/$(MODULE_NAME).v --trace

clean:
	$(RM) ./obj_dir/*

include ../Makefile
