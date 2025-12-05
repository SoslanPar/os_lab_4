CC=gcc
CFLAGS=-I src -O2 -fPIC

all: libv1.so libv2.so prog1 prog2

libv1.so: src/libv1.c src/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ $< -lm
# $@ - имя цели (libv1.so), $< - первая зависимость (src/libv1.c)

libv2.so: src/libv2.c src/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ $< -lm

prog1: src/prog1_linked.c src/contracts.h libv1.so
	$(CC) -I src -O2 -o $@ src/prog1_linked.c -L . -lv1 -Wl,-rpath,.
# -L . — искать библиотеки в текущей папке
# -lv1 — линковать с libv1.so
# 	Линковщик автоматически преобразует -lИМЯ в libИМЯ.so (или libИМЯ.a для статических)
# -Wl,-rpath,. — прописать в исполняемом файле путь поиска .so = текущая папка
# 	-Wl, — передать следующий аргумент линковщику (ld), а не компилятору
# 	-rpath — установить RPATH (runtime library search path)
# 	. — текущая папка

prog2: src/prog2_runtime.c src/contracts.h libv1.so libv2.so
	$(CC) -I src -O2 -o $@ src/prog2_runtime.c -ldl -lm -Wl,-rpath,.
# -ldl — линковать с libdl (для dlopen/dlsym/dlclose)

clean:
	rm -f libv1.so libv2.so prog1 prog2
