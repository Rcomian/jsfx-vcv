RACK_DIR ?= ../../..
.NOTPARALLEL:

CD = cd

# Target paths

include $(RACK_DIR)/arch.mk

ifdef ARCH_LIN
	jsusfx = lib/jsusfx.a
endif

ifdef ARCH_MAC
	jsusfx = lib/jsusfx.a
endif

ifdef ARCH_WIN
	jsusfx = lib/jsusfx.a
endif

#DEPS += $(openmpt)
DEPS += $(jsusfx)
include $(RACK_DIR)/dep.mk


# Targets

$(jsusfx):
	$(WGET) "https://github.com/Rcomian/jsusfx/archive/v0.4.0b1b.tar.gz"
	$(UNTAR) v0.4.0b1b.tar.gz
	cd jsusfx-0.4.0b1b; $(CMAKE) src
	$(MAKE) -C jsusfx-0.4.0b1b


clean:
	git clean -fdx
	git submodule foreach git clean -fdx
