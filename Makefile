CC = clang
CFLAGS = -Wall -g -Ofast -std=c99
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lGL

BUILDDIR = build

# The base directory for source files
SRCDIR = src
# List of all source files in the project
SRCS = $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/*.c)
# Subdirectories in the src directory
SUBDIRS = $(shell find src/* -type d -exec basename {} \;)

# Output directory for object files
OBJDIR = $(BUILDDIR)/obj
# Use the same structure for object files as source files
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJSUBDIRS = $(OBJDIR)/$(SUBDIRS)

BIN = $(BUILDDIR)/main

all: $(BIN)

$(BUILDDIR):
	$(info Creating build directory)
	@mkdir -p $@

$(OBJDIR): $(BUILDDIR)
	$(info Creating objects directory $@)
	@mkdir -p $@

$(OBJSUBDIRS): $(OBJDIR)
	$(info Creating objects directory $@)
	@mkdir -p $@

$(BIN): $(BUILDDIR) $(OBJS)
	$(info Linking $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	$(info Compiling $<)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
