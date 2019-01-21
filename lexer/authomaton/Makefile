#set CONFIG_TEST=y to build test application for the sources

target = libnfa.a
test-target = unit_test

all-obj = $(wildcard *.cpp)
obj = $(patsubst %.cpp,%.o,$(filter-out test%,$(all-obj)))
test-obj = $(patsubst %.cpp,%.o,$(filter test%,$(all-obj)))
$(info test-obj=$(test-obj), obj=$(obj))


all: build $(BUILD_TEST) $(RUN_TEST) install 

build:  $(obj)
	$(AR) rcs $(target) *.o

install:
	cp $(target) $(BUILD_DIR)

$(TEST_TARGET):

prepare: