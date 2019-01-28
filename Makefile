include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build
export CXXFLAGS += -I$(TOPDIR)/include -g --std=c++17
export CFLAGS += -I$(TOPDIR)/include -g
export LDFLAGS += -L$(BUILD_DIR) -ldl

ifeq ($(CONFIG_MEMCHECK), y)
export CXXFLAGS += -fsanitize=address
export CFLAGS += -fsanitize=address
endif

ifeq ($(CONFIG_PROFILE), y)
export CXXFLAGS += -pg -O0
export CFLAGS += -pg -O0
export LDFLAGS += -pg
else

ifeq ($(CONFIG_RELEASE), y)
export CXXFLAGS += -O2 -Wall
export CFLAGS += -O2 -Wall
endif

endif



SUBDIRS = core regexp_parser lexer parser

all: $(SUBDIRS)

$(SUBDIRS): .prepare
	$(MAKE) -C $@ all

.prepare:
	mkdir $(BUILD_DIR) | true
	for i in $(SUBDIRS); do \
		make -C $${i} prepare; \
	done
	touch .prepare

.PHONY: all $(SUBDIRS)
