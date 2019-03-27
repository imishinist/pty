CC := gcc

.PHONY: all
all: pty

pty: pty.o error.o pty_fork.o loop.o signal.o pipe.o io.o driver.o
	$(CC) -o pty pty.o error.o pty_fork.o loop.o signal.o pipe.o io.o driver.o

pty.o: pty.c
	$(CC) -c pty.c

error.o: error.c
	$(CC) -c error.c

pty_fork.o: pty_fork.c
	$(CC) -c pty_fork.c

loop.o: loop.c
	$(CC) -c loop.c

signal.o: signal.c
	$(CC) -c signal.c

pipe.o: pipe.c
	$(CC) -c pipe.c

io.o: io.c
	$(CC) -c io.c

driver.o: driver.c
	$(CC) -c driver.c


.PHONY: clean
clean:
	rm -rf pty pty.o error.o pty_fork.o loop.o signal.o pipe.o io.o driver.o pty.h.gch
