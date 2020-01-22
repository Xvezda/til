.PHONY: libs test


all: static shared test

static:
	cd src && $(MAKE) clean && $(MAKE) static

shared:
	cd src && $(MAKE) clean && $(MAKE) shared

test:
	cd tests && $(MAKE) test

clean:
	cd libs && rm -rf *.so *.a
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean

