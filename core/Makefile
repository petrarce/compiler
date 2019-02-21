target=
LOCAL_LDFLAGS=
DEPS= authomaton symb_tbl syntax_tree

all-obj = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(filter-out test%,$(all-obj)))
include $(TOPDIR)/Makefile.test

all: $(DEPS)

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
