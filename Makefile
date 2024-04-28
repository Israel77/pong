CC = clang
CFLAGS = -Wall -g -Ofast -std=c99
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lGL 

SRCDIR = src
BUILDDIR = build

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))


$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/main: $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/main
