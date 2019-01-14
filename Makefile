include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build
export CXXFLAGS += -I$(TOPDIR)/include -g --std=c++17 -fsanitize=address
export CFLAGS += -I$(TOPDIR)/include -g -fsanitize=address
export LDFLAGS += -L$(BUILD_DIR)

SUBDIRS = lexer parser

all: $(SUBDIRS)

$(SUBDIRS): prepare
	@$(MAKE) -C $@

prepare:
	@mkdir $(BUILD_DIR) | true
	for i in $(SUBDIRS); do \
		make -C $${i} prepare; \
	done

.PHONY: all $(SUBDIRS) prepare
