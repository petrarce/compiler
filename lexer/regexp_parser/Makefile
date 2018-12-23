#set CONFIG_TEST=y to build test application for the sources
src 	:= $(wildcard *.cpp)
objects := $(patsubst %.cpp,%.o,$(src))
yacc	:= $(wildcard *.ypp)
yacc-obj := $(patsubst %.ypp,%.tab.o,$(yacc))
ifeq ($(CONFIG_TEST),y)
	target = test_main
else
	target = libfinit_regexparser.a
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif



.PHONY: all $(yacc-obj) $(yacc)

all: build install

$(yacc-obj): $(yacc)
	echo =======$@
	$(CXX) $(CFLAGS) -c $(patsubst %.o,%.cpp,$@) -o $@

$(yacc):
	echo =======$@
	bison $@

build: $(yacc-obj) $(objects)
	echo =======build
ifeq ($(CONFIG_TEST),y)
	$(CXX) $(CXXFLAGS) -o test_main $(objects) $(yacc-obj)
else
	$(AR) rcs $(target) $(objects)
endif 



install:
	cp $(target) $(BUILD_DIR)