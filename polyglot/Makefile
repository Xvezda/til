CC = gcc
CCFLAGS= -w
SOURCE = polyglot.txt
TARGETS = polyglot_c polyglot_py polyglot_php


# Executables
all: $(TARGETS)

test: all
	./run_tests.sh

polyglot.%:
	cp $(SOURCE) $@

polyglot_c: polyglot.c
	$(CC) $(CCFLAGS) $< -o $@

polyglot_py: polyglot.py
	echo "#!/usr/bin/env python3" >> $@
	cat $< >> $@
	chmod +x $@

polyglot_php: polyglot.php
	echo "#!/usr/bin/env bash" >> $@
	echo "php $<" >> $@
	chmod +x $@

clean:
	rm -f $(TARGETS) $(filter-out $(SOURCE), $(wildcard polyglot.*))
