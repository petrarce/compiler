#set CONFIG_TEST=y to build test application for the sources
src 	:= $(wildcard *.cpp)
objects := $(patsubst %.cpp,%.o,$(src))
yacc	:= $(wildcard *.ypp)
yacc-obj := $(patsubst %.ypp,%.tab.o,$(yacc))
yacc-hdr := $(patsubst %.ypp,%.tab.hpp,$(yacc))
yacc-src := $(patsubst %.ypp,%.tab.cpp,$(yacc))
$(info DEBUG: yacc=$(yacc))

ifeq ($(CONFIG_TEST),y)
	target = 
	LOCAL_LDFLAGS +=
else
	target =
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif



.PHONY: all build install prepare

all: build install

$(yacc-obj): $(yacc-src)
	echo =======$@
	$(CXX) $(CFLAGS) -c $(patsubst %.o,%.cpp,$@) -o $@

$(yacc-src):
	echo =======$@
	bison -v -d $(patsubst %.tab.cpp,%.ypp,$@)

build: $(yacc-obj) $(objects)
	echo =======build
ifeq ($(CONFIG_TEST),y)
	$(CXX) $(CXXFLAGS) -o $(target) *.o $(LDFLAGS) $(LOCAL_LDFLAGS)
else
	$(AR) rcs $(target) *.o
endif 

install:
	cp $(target) $(BUILD_DIR)

prepare: $(yacc-src)
	mv $(yacc-hdr) $(TOPDIR)/include
