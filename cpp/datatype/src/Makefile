AR = ar
CC = g++
CPP = $(CC)
CPPFLAGS = -std=c++14 -Wall -Wextra -pedantic
INC = -I../include
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

all: build

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INC) -c $< -o $@

static: ../libs/static/libxvzd.a

shared: ../libs/shared/libxvzd.so

../libs/static/libxvzd.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

../libs/shared/libxvzd.so: CPPFLAGS += -fPIC
../libs/shared/libxvzd.so: $(OBJS)
	$(CPP) -shared -o $@ $(OBJS)

build: static shared

debug: CPPFLAGS+=-O0 -g -DDEBUG
debug: $(OBJS)

clean:
	rm -rf $(OBJS) *.dSYM

