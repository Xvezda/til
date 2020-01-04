.SUFFIXES: .cc

CC = g++
CXX = $(CC)
SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
TARGETS = $(patsubst %.o,%,$(OBJS))



all: $(TARGETS)

%: %.o

%.o: %.cc

clean:
	rm -rf $(OBJS) $(TARGETS)
