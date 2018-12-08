include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build
export CXXFLAGS += -I$(TOPDIR)/include -g

SUBDIRS = lexer

all: prepare $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

prepare:
	@mkdir $(BUILD_DIR) | true

.PHONY: all $(SUBDIRS) prepare