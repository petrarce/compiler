target = regexp
LOCAL_LDFLAGS=-lnfa
DEPS=

all-obj = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(filter-out test%,$(filter-out main%,$(all-obj))))
obj-main = $(patsubst %.cpp,%.o,$(filter main%,$(all-obj)))

include $(TOPDIR)/Makefile.test

yacc	:= $(wildcard *.ypp)
yacc-obj := $(patsubst %.ypp,%.tab.o,$(yacc))
yacc-hdr := $(patsubst %.ypp,%.tab.hpp,$(yacc))
yacc-src := $(patsubst %.ypp,%.tab.cpp,$(yacc))

prepare: $(yacc-src)

$(yacc-obj): $(yacc-src)
	echo =======$@
	$(CXX) $(CFLAGS) -c $(patsubst %.o,%.cpp,$@) -o $@

$(yacc-src):
	echo =======$@
	bison -v -d $(patsubst %.tab.cpp,%.ypp,$@)

all: $(DEPS) build app $(RUN_TEST) install 

build:  $(obj)
	$(AR) rcs lib$(target).a $(obj)

app: $(obj-main)
	$(CXX) $(CXXFLAGS) -o $(target) $(obj-main) $(obj) -L. -l$(target) $(LOCAL_LDFLAGS) $(LDFLAGS)	

install:
	cp lib$(target).a $(BUILD_DIR)

$(DEPS):
	$(MAKE) -C $@ all



.PHONY: all build install $(DEPS)
