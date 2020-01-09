CC = gcc
CCFLAGS= -w
SOURCE = polyglot.txt
TARGETS = polyglot_c polyglot_py


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

clean:
	rm -f $(TARGETS) $(filter-out $(SOURCE), $(wildcard polyglot.*))
