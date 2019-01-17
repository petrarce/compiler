#set CONFIG_TEST=y to build test application for the sources
$(info CFLAGS=$(CFLAGS))

objects = $(subst 	cpp,o,$(shell find *.cpp))
ifeq ($(CONFIG_TEST),y)
	target = test_main
else
	target = libnfa.a
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif


all: build install
build:  $(objects)
ifeq ($(CONFIG_TEST),y)
	$(CXX) $(CXXFLAGS) -o test_main $(objects) $(LDFLAGS)
else
	$(AR) rcs $(target) *.o
endif 
install:
	cp $(target) $(BUILD_DIR)

prepare: