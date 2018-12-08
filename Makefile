include Makefile.config

src-{CONFIG_LEXER} = lexer

all: $(SUBDIRS)
	$(MAKE) $@

.PHONY: all $(SUBDIRS)