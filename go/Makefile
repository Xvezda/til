SRCS = $(wildcard *.go)
TARGETS = $(patsubst %.go,%,$(SRCS))


all: $(TARGETS)

%: %.go
	go build $<

clean:
	rm -rf $(TARGETS)
