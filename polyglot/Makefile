CC = gcc
CCFLAGS= -w
SOURCE = polyglot.txt


# Executables
all: polyglot_c polyglot_py

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
	rm -f polyglot.c polyglot.py
