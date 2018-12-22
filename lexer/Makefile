SUBDIRS := authomaton
SUBDIRS += regexp_parser

all: $(SUBDIRS)
$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: all $(SUBDIRS)
