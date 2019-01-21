include Makefile.config

#global variables exports
export TOPDIR = $(shell realpath .)
export BUILD_DIR := $(TOPDIR)/build
export CXXFLAGS += -I$(TOPDIR)/include -g --std=c++17 -fsanitize=address
export CFLAGS += -I$(TOPDIR)/include -g -fsanitize=address
export LDFLAGS += -L$(BUILD_DIR) -ldl

SUBDIRS = lexer parser symb_tbl

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
