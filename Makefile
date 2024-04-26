CC = clang
CFLAGS = -Wall -g
LDFLAGS = -lraylib -lm -lpthread -ldl -lrt -lGL 

SRCDIR = src
BUILDDIR = build

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/ball.c $(SRCDIR)/paddle.c

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/ball.o $(BUILDDIR)/paddle.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/main: $(OBJECTS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/ball.o: $(SRCDIR)/ball.c $(SRCDIR)/ball.h

$(BUILDDIR)/paddle.o: $(SRCDIR)/paddle.c $(SRCDIR)/paddle.h

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/main
