ARCH=armv7a
ANDROID_API_LEVEL=21

ifeq ($(ARCH), armv7a)
	CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ARCH)-linux-androideabi$(ANDROID_API_LEVEL)-clang
else
	CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ARCH)-linux-android$(ANDROID_API_LEVEL)-clang
endif

.PHONY: all
all: edu-edition-all-ports

.PHONY: clean
clean:
	$(RM) edu-edition-all-ports
