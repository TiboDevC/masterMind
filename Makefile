CC     ?= gcc
CXX    ?= g++
TARGET := mastermind

DIR_ROOT_PREFIX := .
OBJDIR          := objs

# Declare all source file
SRC_FILE       := main.cpp
SRC_FILE       += mastermind.cpp

TARGET_CC_SRC  :=
TARGET_CXX_SRC := $(SRC_FILE)

TARGET_INCLUDE  :=
TARGET_INCLUDE  := $(addprefix -I$(DIR_ROOT_PREFIX)/, $(TARGET_INCLUDE))

TARGET_EXE_OUTPUT := $(OBJDIR)/$(TARGET)

CCFLAGS  := -Wall -Wextra -Werror -Os
CCFLAGS  += $(TARGET_INCLUDE)
CXXFLAGS := -std=c++20

LDFLAGS  := -static

TARGET_OBJ     := $(patsubst %.cpp,$(OBJDIR)/%.o,$(TARGET_CXX_SRC)) \
                  $(patsubst %.c,$(OBJDIR)/%.o,$(TARGET_CC_SRC))
TARGET_OBJ_DEP := $(TARGET_OBJ:.o=.d)

.PHONY: clean $(TARGET)

all: $(TARGET)

V ?= 0
_V_CC_0        = @echo "  CC      " $<;
_V_CXX_0       = @echo "  CXX     " $<;
_V_LD_0        = @echo "  LD      " $@;
_V_CLEAN_0     = @echo "  CLEAN";

# Include dependencies on *.h files
-include $(TARGET_OBJ_DEP)

$(OBJDIR)/%.o: $(DIR_ROOT_PREFIX)/%.c
	@mkdir -p $(abspath $(dir $@))
	$(_V_CC_$(V))$(CC) $(CCFLAGS) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(DIR_ROOT_PREFIX)/%.cpp
	@mkdir -p $(abspath $(dir $@))
	$(_V_CXX_$(V))$(CXX) $(CCFLAGS) $(CXXFLAGS) -c -o $@ $<

# Add dependency to Makefile
$(TARGET_OBJ): Makefile

$(TARGET_EXE_OUTPUT): $(TARGET_OBJ)
	$(_V_LD_$(V))$(CXX) $(CCFLAGS) $(LDFLAGS) -o $@ $(TARGET_OBJ)

$(TARGET): $(TARGET_EXE_OUTPUT)

clean:
	$(_V_CLEAN_$(V))rm -rf $(OBJDIR) $(LCOV_DIR) $(REPORT_DIR)
