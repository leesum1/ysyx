NAME = sdlpal
INC_DIR += ./include
BUILD_DIR ?= ./build

OBJ_DIR ?= $(BUILD_DIR)/
BINARY ?= $(BUILD_DIR)/$(NAME)

.DEFAULT_GOAL = app

# Compilation flags
CC  = gcc
CXX = g++
LD  = g++
INCLUDES  = $(addprefix -I, $(INC_DIR))
CFLAGS   += -O2 -MMD -Wall $(INCLUDES) `sdl-config --cflags`
CXXFLAGS += $(CFLAGS)

# Files to be compiled
C_SRCS   = $(shell find src/ -name "*.c")
CXX_SRCS = $(shell find src/ -name "*.cpp")
OBJS = $(C_SRCS:src/%.c=$(OBJ_DIR)/%.o) $(CXX_SRCS:src/%.cpp=$(OBJ_DIR)/%.o) 

# Compilation patterns
$(OBJ_DIR)/%.o: src/%.c
	@echo + CC $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: src/%.cpp
	@echo + CXX $<
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<


# Depencies
-include $(OBJS:.o=.d)

# Some convenient rules

.PHONY: app clean
app: $(BINARY)

$(BINARY): $(OBJS)
	@echo + LD $@
	@$(LD) -O2 -o $@ $^ `sdl-config --libs`

run: app
	ln -sf ../data $(BUILD_DIR)/
	$(BINARY)

clean:
	-rm -rf $(BUILD_DIR)
