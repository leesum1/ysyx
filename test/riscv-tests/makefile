#=======================================================================
# Makefile for riscv-tests/isa
#-----------------------------------------------------------------------

XLEN = 64

src_dir := ./isa

include $(src_dir)/rv64ui/Makefrag
include $(src_dir)/rv64uc/Makefrag
include $(src_dir)/rv64um/Makefrag
include $(src_dir)/rv64ua/Makefrag
include $(src_dir)/rv64uf/Makefrag
include $(src_dir)/rv64ud/Makefrag
include $(src_dir)/rv64uzfh/Makefrag
include $(src_dir)/rv64si/Makefrag
include $(src_dir)/rv64ssvnapot/Makefrag
include $(src_dir)/rv64mi/Makefrag
include $(src_dir)/rv64mzicbo/Makefrag

$(shell mkdir -p build/elf build/bin build/dump)

default: all

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= /opt/riscv/bin/riscv$(XLEN)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles 
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
RISCV_SIM ?= spike
RISCV_OBJCOPY ?= $(RISCV_PREFIX)objcopy

vpath %.S $(src_dir)


#------------------------------------------------------------
# Build assembly tests

%.dump: %
	$(RISCV_OBJDUMP) build/elf/$< > build/dump/$@

%.bin: %
	$(RISCV_OBJCOPY) -O binary build/elf/$<  build/bin/$<.bin


define compile_template

$$($(1)_p_tests): $(1)-p-%: $(1)/%.S
	$$(RISCV_GCC) $(2) $$(RISCV_GCC_OPTS) -I$(src_dir)/../env/p -I$(src_dir)/macros/scalar -T$(src_dir)/../env/p/link.ld $$< -o build/elf/$$@

$(1)_tests += $$($(1)_p_tests)
$(1)_tests_dump = $$(addsuffix .dump, $$($(1)_tests))

$(1): $$($(1)_tests_dump)

.PHONY: $(1)

COMPILER_SUPPORTS_$(1) := $$(shell $$(RISCV_GCC) $(2) -c -x c /dev/null -o /dev/null 2> /dev/null; echo $$$$?)

ifeq ($$(COMPILER_SUPPORTS_$(1)),0)
tests += $$($(1)_tests)
endif

endef


$(eval $(call compile_template,rv64ui,-march=rv64g -mabi=lp64))
# $(eval $(call compile_template,rv64uc,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64um,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64ua,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64si,-march=rv64g -mabi=lp64))
$(eval $(call compile_template,rv64mi,-march=rv64g -mabi=lp64))






tests_dump = $(addsuffix .dump, $(tests))
tests_bin = $(addsuffix .bin, $(tests))


#------------------------------------------------------------
# Default

all: $(tests_dump) $(tests_bin)

#------------------------------------------------------------
# Clean up

clean:
	rm -rf build
