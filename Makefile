ARCH ?= armv7a
ANDROID_API_LEVEL ?= 21
PROGRAMS=edu-edition-all-ports-server edu-edition-all-ports-tester
ANDROID_CFLAGS ?= $(CFLAGS)

ifeq ($(ARCH), armv7a)
	ANDROID_CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ARCH)-linux-androideabi$(ANDROID_API_LEVEL)-clang
else
	ANDROID_CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ARCH)-linux-android$(ANDROID_API_LEVEL)-clang
endif

.PHONY: all
all: $(PROGRAMS)

.PHONY: clean
clean:
	$(RM) $(PROGRAMS)

edu-edition-all-ports-server: edu-edition-all-ports-server.c
	$(ANDROID_CC) -o $@ $< $(ANDROID_CFLAGS)
