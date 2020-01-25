GO = go
SRCS = $(wildcard *.go)
TARGETS = $(patsubst %.go,%,$(SRCS))


all: $(TARGETS)

%: %.go
	$(GO) build $<

clean:
	rm -rf $(TARGETS)
