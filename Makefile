include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build


TMPSUBDIRS := $(wildcard */.)
SUBDIRS = $(filter-out build/.,$(TMPSUBDIRS))

all: prepare $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

prepare:
	@mkdir $(BUILD_DIR) | true

.PHONY: all $(SUBDIRS) prepare