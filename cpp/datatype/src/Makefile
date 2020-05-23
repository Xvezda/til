AR = ar
CC = g++
CPP = $(CC)
CPPFLAGS = -std=c++14 -Wall -Wextra -pedantic
INC = -I../include
SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))
STATIC_PATH = ../libs/static
SHARED_PATH = ../libs/shared

all: build

$(STATIC_PATH)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INC) -c $< -o $@

$(SHARED_PATH)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INC) -c $< -o $@

static: $(STATIC_PATH)/libxvzd.a

shared: $(SHARED_PATH)/libxvzd.so

$(STATIC_PATH)/libxvzd.a: $(addprefix $(STATIC_PATH)/, $(OBJ_FILES))
	$(AR) rcs $@ $(addprefix $(STATIC_PATH)/, $(OBJ_FILES))

$(SHARED_PATH)/libxvzd.so: CPPFLAGS += -fPIC
$(SHARED_PATH)/libxvzd.so: $(addprefix $(SHARED_PATH)/, $(OBJ_FILES))
	$(CPP) -shared -o $@ $(addprefix $(SHARED_PATH)/, $(OBJ_FILES))

build: static shared

debug: CPPFLAGS += -O0 -g -DDEBUG
debug: build

clean:
	rm -rf $(SHARED_PATH)/*.o $(STATIC_PATH)/*.o *.dSYM

