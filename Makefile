CC = clang
CFLAGS = -Wall -g -O0 -std=c99
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
OBJSUBDIRS = $(addprefix $(OBJDIR)/, $(SUBDIRS))

# Dependencies for running the tuning executable
TUNINGDEPS = $(addprefix $(OBJDIR)/, tuning.o ai/battle.o ai/cpu.o ai/pid.o \
	core/ball.o core/collisions.o core/defs.o core/paddle.o)

BIN = $(BUILDDIR)/main

all: $(BIN)

tune: $(TUNINGDEPS) $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TUNINGDEPS) -o $(BUILDDIR)/tuning

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
	$(CC) $(CFLAGS) $(LDFLAGS) $(filter-out $(OBJDIR)/tuning.o, $(OBJS)) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	$(info Compiling $<)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
