target = nfa
LOCAL_LDFLAGS=
DEPS=

all-obj = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(filter-out test%,$(all-obj)))
include $(TOPDIR)/Makefile.test

all: $(DEPS) build $(RUN_TEST) install 

build:  $(obj)
	$(AR) rcs lib$(target).a $(obj)

install:
	cp lib$(target).a $(BUILD_DIR)

$(DEPS):
	$(MAKE) -C $@ all

prepare:

.PHONY: all build install $(DEPS)