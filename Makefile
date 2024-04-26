CC = clang
CFLAGS = -Wall -g
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lGL 

SRCDIR = src
BUILDDIR = build

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/ball.o $(BUILDDIR)/paddle.o $(BUILDDIR)/cpu.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/main: $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/main
