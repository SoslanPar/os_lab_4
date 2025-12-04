CC=gcc
CFLAGS=-I src -O2 -fPIC
LDFLAGS=

# Shared libraries for WSL/Linux
all: libv1.so libv2.so prog1 prog2

libv1.so: src/libv1.c src/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ $< -lm

libv2.so: src/libv2.c src/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ $< -lm

prog1: src/prog1_linked.c src/contracts.h libv1.so
	$(CC) -I src -O2 -o $@ src/prog1_linked.c -L . -lv1 -Wl,-rpath,.

prog2: src/prog2_runtime.c src/contracts.h libv1.so libv2.so
	$(CC) -I src -O2 -o $@ src/prog2_runtime.c -ldl -lm -Wl,-rpath,.

clean:
	rm -f libv1.so libv2.so prog1 prog2
