CFLAGS   = -Wall -Wextra -mtune=native -no-pie `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = 0 1 2 3

.PHONY: all
all: $(TARGETS)
0: $(srcdir)helper.c $(srcdir)0.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

1: $(srcdir)1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

2: $(srcdir)2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3: $(srcdir)helper.c $(srcdir)3.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

