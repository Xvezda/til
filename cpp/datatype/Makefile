.PHONY: libs test


all: static shared test

static:
	cd src && $(MAKE) static && $(MAKE) clean

shared:
	cd src && $(MAKE) shared && $(MAKE) clean

test:
	cd tests && $(MAKE)

clean:
	cd libs && rm -rf *.so *.a
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean

