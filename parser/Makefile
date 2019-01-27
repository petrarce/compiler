target = parser
LOCAL_LDFLAGS=-lnfa -llexer
DEPS=

all-obj = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(filter-out test%,$(all-obj)))
include $(TOPDIR)/Makefile.test

yacc	:= $(wildcard *.ypp)
yacc-obj := $(patsubst %.ypp,%.tab.o,$(yacc))
yacc-hdr := $(patsubst %.ypp,%.tab.hpp,$(yacc))
yacc-src := $(patsubst %.ypp,%.tab.cpp,$(yacc))

prepare: $(yacc-src)
	mv while_grammar.tab.hpp ${TOPDIR}/include

$(yacc-obj): $(yacc-src)
	echo =======$@
	$(CXX) $(CFLAGS) -c $(patsubst %.o,%.cpp,$@) -o $@

$(yacc-src):
	echo =======$@
	bison -v -d $(patsubst %.tab.cpp,%.ypp,$@)

all: $(DEPS) build $(RUN_TEST) install 

build:  $(obj)
	$(AR) rcs lib$(target).a $(obj)

install:
	cp lib$(target).a $(BUILD_DIR)

$(DEPS):
	$(MAKE) -C $@ all



.PHONY: all build install $(DEPS)
