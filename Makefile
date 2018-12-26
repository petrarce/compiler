include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build
export CXXFLAGS += -I$(TOPDIR)/include -g --std=c++17 -fsanitize=address
export CFLAGS += -I$(TOPDIR)/include -g -fsanitize=address
export LDFLAGS += -L$(BUILD_DIR)

SUBDIRS = lexer

all: prepare $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

prepare:
	@mkdir $(BUILD_DIR) | true

.PHONY: all $(SUBDIRS) prepare
