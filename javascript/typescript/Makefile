TS = tsc
SRC_FILES = $(wildcard *.ts)
TARGET_FILES = $(patsubst %.ts, %.js, $(SRC_FILES))

$(TARGET_FILES): $(SRC_FILES)
	$(TS) $<
