CC=gcc
CFLAGS=-Iinclude -Wall

all: rtos

rtos: src/task.o src/scheduler.o test/test_tasks.o
	$(CC) -o rtos $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test/%.o: test/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o test/*.o rtos