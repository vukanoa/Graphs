CC      := gcc
CFLAGS  := -O0 -g -Wall -fsanitize=address
TARGET  := program
BUILD   := build
SRCDIR  := src
HDRDIR  := hdr
HDRS    := -I$(HDRDIR)
SRCS    := $(wildcard $(SRCDIR)/*.c)
OBJS    := $(patsubst $(SRCDIR)/%.c,$(BUILD)/%.o,$(SRCS))
DEPS    := $(patsubst $(SRCDIR)/%.c,$(BUILD)/%.d,$(SRCS))

.PHONY = all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRCDIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

$(BUILD)/%.d: $(SRCDIR)/%.c | $(BUILD)
	$(CC) $(HDRS) -MM -MT $(BUILD)/$*.o $< > $@

include $(DEPS)

$(BUILD):
	mkdir build

clean:
	rm -rf $(TARGET) $(BUILD)



