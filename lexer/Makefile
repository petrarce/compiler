target = lexer
LOCAL_LDFLAGS=-lnfa -lregexp
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
	for i in $(DEPS); do \
		make -C $${i} prepare; \
	done

.PHONY: all build install $(DEPS)
