API ?= 35
TARGET ?= oneplus

NDK_ROOT ?= $(or $(ANDROID_NDK_HOME),$(ANDROID_NDK_ROOT))
NDK_CC := $(NDK_ROOT)/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$(API)-clang

SRCS := \
  src/core/main.c \
  src/core/util.c \
  src/core/slide.c \
  src/core/fops.c \
  src/core/pipe_physrw.c \
  src/core/root.c \
  src/core/miniadb.c \
  src/core/umh_root.c

# Default target.h for ghostlock-oneplus
TARGET_H := target.h
ifeq ($(TARGET),spacewar)
  TARGET_H := devices/spacewar/target.h
endif

CFLAGS := -O2 -Wall -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function \
  -Isrc/core -Isrc/devices -DTARGET_CONFIG_H=\"$(TARGET_H)\"
LDFLAGS := -fPIE -pie -pthread

.PHONY: all clean

all: ghostlock

ghostlock: $(SRCS)
	$(NDK_CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f ghostlock
