.PHONY: lib test


all: lib test

lib:
	cd src && $(MAKE)

test:
	cd tests && $(MAKE)

clean:
	cd lib && rm -rf *.so
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean

