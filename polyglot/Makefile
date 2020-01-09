CC = gcc
CCFLAGS= -w
SOURCE = polyglot.txt
TARGETS = polyglot_c polyglot_py polyglot_php


# Executables
all: $(TARGETS)

test:
	./run_tests.sh

polyglot.%:
	cp $(SOURCE) $@

polyglot_c: polyglot.c
	$(CC) $(CCFLAGS) $< -o $@

polyglot_py: polyglot.py
	echo "#!/usr/bin/env python" > $@
	cat $< >> $@
	chmod +x $@

polyglot_php: polyglot.php
	echo "#!/usr/bin/env bash" >> $@
	echo "php $<" >> $@
	chmod +x $@

clean:
	rm -f $(TARGETS) $(shell echo $(TARGETS) | sed 's/_/./g')
