include ../Makefile.config

objects = $(subst 	cpp,o,$(shell find *.cpp))
$(info DEBUG objects = $(objects))
ifeq ($(CONFIG_TEST),y)
	target = test_main
else
	target = libfinit_automaton.a
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif
$(info DEBUG objects = $(objects))


all: $(objects)
ifeq ($(CONFIG_TEST),y)
	$(CXX) -g -o test_main $(objects)
else
	$(AR) rcs $(target) $(objects)
endif 