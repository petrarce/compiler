#set CONFIG_TEST=y to build test application for the sources

objects = $(subst 	cpp,o,$(shell find *.cpp))
ifeq ($(CONFIG_TEST),y)
	target = test_main
else
	target = libfinit_automaton.a
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif


all: $(objects)
ifeq ($(CONFIG_TEST),y)
	$(CXX) -g -o test_main $(objects)
else
	$(AR) rcs $(target) $(objects)
endif 