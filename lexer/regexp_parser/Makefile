#set CONFIG_TEST=y to build test application for the sources
objects = $(subst 	c,o,$(shell find *.c))
yacc	= $(wildcard *.yacc)
yacc-obj = $(patsubst %.yacc,%.tab.o,$(yacc))
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
	$(CC) $(CFLAGS) -c $(patsubst %.o,%.c,$@) -o $@

$(yacc):
	echo =======$@
	yacc -v -b $(patsubst %.yacc,%,$@) $@

build: $(yacc-obj) $(objects)
	echo =======build
ifeq ($(CONFIG_TEST),y)
	$(CC) $(CFLAGS) -o test_main $(objects)
else
	$(AR) rcs $(target) $(objects)
endif 



install:
	cp $(target) $(BUILD_DIR)