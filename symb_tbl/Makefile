DEPS := 

#set CONFIG_TEST=y to build test application for the sources
$(info CFLAGS=$(CFLAGS))

objects = $(subst 	cpp,o,$(shell find *.cpp))
ifeq ($(CONFIG_TEST),y)
	target = test_main
	LOCAL_LDFLAGS +=
else
	target = libstbl.a
	tmpobjects := $(objects)
	objects = $(filter-out test_main.o,$(tmpobjects))
endif


all: $(DEPS) build install

build:  $(objects)
ifeq ($(CONFIG_TEST),y)
	$(CXX) $(CXXFLAGS) -o $(target)  $(objects) $(LDFLAGS) $(LOCAL_LDFLAGS)
else
	$(AR) rcs $(target) *.o
endif 

install:
	cp $(target) $(BUILD_DIR)

$(DEPS):
	$(MAKE) -C $@

prepare:
	for i in $(DEPS); do \
		make -C $${i} prepare; \
	done

.PHONY: all build install $(DEPS)
